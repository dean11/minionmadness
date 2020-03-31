#ifndef MINION_MATH_H
#define MINION_MATH_H

#include <assert.h>
#include <memory>

namespace minion
{
	template <typename T>
	struct tVec2
	{
		typedef tVec2<T> type;
		static const int components = 2;

		union
		{
			struct { T x, y; };
			struct { T r, g; };
		};

		tVec2()
		{
			memset((&x), 0, sizeof(T) * components);
		}
		tVec2(T _x, T _y)
		{
			x = _x;
			y = _y;
		}
		tVec2(T v[components])
		{
			memcpy((&x), &v[0], sizeof(v));
		}

		const T& operator[](const int index) const
		{
			assert(index >= 0 && index < components);
			return (&x)[index];
		}
		T& operator[](const int index)
		{
			assert(index >= 0 && index < components);
			return (&x)[index];
		}
		operator const T*() const
		{
			return (&x);
		}
		operator T*()
		{
			return (&x);
		}
	};

	template <typename T>
	struct tVec3
	{
		typedef tVec3<T> type;
		static const int components = 3;

		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		tVec3()
		{
			memset((&x), 0, sizeof(T) * components);
		}
		tVec3(T _x, T _y, T _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}
		tVec3(T v[components])
		{
			memcpy((&x), &v[0], sizeof(v));
		}

		const T& operator[](const int index) const
		{
			assert(index >= 0 && index < components);
			return (&x)[index];
		}
		T& operator[](const int index)
		{
			assert(index >= 0 && index < components);
			return (&x)[index];
		}
		operator const T*() const
		{
			return (&x);
		}
		operator T*()
		{
			return (&x);
		}
	};

	template <typename T>
	struct tVec4
	{
		typedef tVec4<T> type;
		static const int components = 4;

		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};

		tVec4()
		{
			memset((&x), 0, sizeof(T) * components);
		}
		tVec4(T _x, T _y, T _z, T _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}
		tVec4(T v[components])
		{
			memcpy((&x), &v[0], sizeof(v));
		}

		const T& operator[](const int index) const
		{
			assert(index >= 0 && index < components);
			return (&x)[index];
		}
		T& operator[](const int index)
		{
			assert(index >= 0 && index < components);
			return (&x)[index];
		}
		operator const T*() const
		{
			return (&x);
		}
		operator T*()
		{
			return (&x);
		}
	};

	template <typename T>
	struct tMat3x3
	{
		tVec3<float> mat[3];
	};

	template <typename T>
	struct tMat4x4
	{
		tVec4<float> mat[4];
	};

	typedef tVec2<float> Vec2;
	typedef tVec3<float> Vec3;
	typedef tVec4<float> Vec4;
	typedef tMat3x3<float> Mat3x3;
	typedef tMat4x4<float> Mat4x4;
}

#endif // !MINION_MATH
