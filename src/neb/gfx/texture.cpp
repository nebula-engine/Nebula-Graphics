#include <string.h>
#include <stdio.h>

#include <GL/glew.h>

#include <neb/core/app/__base.hpp>
#include <neb/core/color/Color.hh>

#include <neb/gfx/texture.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/core/buffer.hpp>

#include <png.h>

std::shared_ptr<neb::gfx::texture>	neb::gfx::texture::makePNG(std::string filename) {
	auto tex(make_shared<neb::gfx::texture>());
	tex->load_png(filename);
	return tex;
}
neb::gfx::texture::texture():
	w_(0), h_(0), png_image_data_(0)
{}
neb::gfx::texture::~texture()
{
}
void			neb::gfx::texture::init_shadow(int w,int h, std::shared_ptr<neb::gfx::context::base> context)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	w_ = w;
	h_ = h;

	genAndBind(context);
	
	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_DEPTH_COMPONENT,
			w_, h_,
			0,
			GL_DEPTH_COMPONENT,
			GL_UNSIGNED_BYTE,
			NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	checkerror("");
}
GLuint		neb::gfx::texture::genAndBind(std::shared_ptr<neb::gfx::context::base> context)
{
	GLuint o;
	
	glGenTextures(1, &o);
	checkerror("glGenTextures");
	glBindTexture(GL_TEXTURE_2D, o);
	checkerror("glBindTexture");

	return o;
}
void	neb::gfx::texture::bind(std::shared_ptr<neb::gfx::context::base> context)
{
	GLuint o;
	
	// this is the function called during drawing
	// this is where we check if the buffer is ready and create it if not
	auto it = buffers_.find(context.get());
	if(it == buffers_.end()) {
		o = init_buffer(context);
	} else {
		o = it->second;
	}
	
	glBindTexture(GL_TEXTURE_2D, o);
	checkerror("glBindTexture");
}
int		neb::gfx::texture::load_png(std::string filename)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	auto app(neb::core::app::__base::global());
	
	filename = app->share_dir_ + "media/texture/" + filename;
	
	png_byte header[8];

	FILE *fp = fopen(filename.c_str(), "rb");
	if (fp == 0)
	{
		perror(filename.c_str());
		exit(0);
	}

	// read the header
	fread(header, 1, 8, fp);

	if (png_sig_cmp(header, 0, 8))
	{
		fprintf(stderr, "error: %s is not a PNG.\n", filename.c_str());
		fclose(fp);
		return 0;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		fprintf(stderr, "error: png_create_read_struct returned 0.\n");
		fclose(fp);
		return 0;
	}

	// create png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		fprintf(stderr, "error: png_create_info_struct returned 0.\n");
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return 0;
	}

	// create png info struct
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		fprintf(stderr, "error: png_create_info_struct returned 0.\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
		fclose(fp);
		return 0;
	}

	// the code in this if statement gets called if libpng encounters an error
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "error from libpng\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return 0;
	}

	// init png reading
	png_init_io(png_ptr, fp);

	// let libpng know you already read the first 8 bytes
	png_set_sig_bytes(png_ptr, 8);

	// read all the info up to the image data
	png_read_info(png_ptr, info_ptr);

	// variables to pass to get info
	int bit_depth, color_type;

	// get info about png
	png_get_IHDR(
			png_ptr, info_ptr,
			&w_, &h_,
			&bit_depth, &color_type,
			NULL, NULL, NULL);
	
	
	
	// Update the png info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Row size in bytes.
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	// glTexImage2d requires rows to be 4-byte aligned
	rowbytes += 3 - ((rowbytes-1) % 4);

	// Allocate the image_data as a big block, to be given to opengl

	png_image_data_ = (png_byte*)malloc(rowbytes * h_ * sizeof(png_byte)+15);
	if (png_image_data_ == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG image data\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		abort();
	}

	// row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep * row_pointers = (png_bytep*)malloc(h_ * sizeof(png_bytep));
	if (row_pointers == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(png_image_data_);
		fclose(fp);
		abort();
	}

	// set the individual row_pointers to point at the correct offsets of image_data
	for (unsigned int i = 0; i < h_; i++)
	{
		row_pointers[h_ - 1 - i] = png_image_data_ + i * rowbytes;
	}

	// read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);

	// Generate the OpenGL texture object

	//printf("image '%s' loaded into texture object %i\n", filename, buf->texture_);

	// clean up
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	//free(image_data);
	free(row_pointers);
	fclose(fp);
	return 0;
}
GLuint			neb::gfx::texture::init_buffer(std::shared_ptr<neb::gfx::context::base> context) {
	
	GLint o = genAndBind(context);

	buffers_[context.get()] = o;
	
	cout << "w " << w_ << " h " << h_ << " data " << (long int)png_image_data_ << endl;

	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			w_, h_,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			png_image_data_);
	checkerror("glTexImage2D");

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	checkerror("glTexParameterf");

	return o;
}



