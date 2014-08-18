#ifndef NEB_GFX_GLSL_ARRAY_HPP
#define NEB_GFX_GLSL_ARRAY_HPP

namespace uniform {
/** @brief array
 * abstract class for managing sequential data arrays.
 * So data for arrays of uniforms can be loaded faster.
 *
 * For example, an array is used for light positions.
 * The core light object is stored elsewhere and registers for a slot in the array.
 *
 * Used by:
 * lights
 *
 */
template<typename R, typename T> class array {
	public:
		array(int n) {
			data = new T[n];
			closed = new int[n];
			objects = new std::weak_ptr<R>[n];
			for(int i = 0; i < n; i++) {
				closed[i] = 0;
			}
		}
		int		register(std::weak_ptr<R> o) {
			// search for empty slot
			int i = 0;
			while(closed[i]) i++;
			
			// assign object to slot
			objects[i] = o;
			
			// mark slot as filled
			
			// return position to object so it can access it later
		}
		
		T*			data;
	private:
		int*			open;
		std::weak_ptr<R>*	objects;
};
}

#endif

