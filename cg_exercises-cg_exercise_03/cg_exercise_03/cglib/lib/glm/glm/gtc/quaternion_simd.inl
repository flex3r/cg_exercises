/// @ref core
/// @file glm/gtc/quaternion_simd.inl

#if GLM_ARCH & GLM_ARCH_SSE2_BIT

namespace glm{
namespace detail
{
/*
	template <precision P>
	struct compute_quat_mul<float, P, true>
	{
		static tquat<float, P> call(tquat<float, P> const& q1, tquat<float, P> const& q2)
		{
			// SSE2 STATS: 11 shuffle, 8 mul, 8 add
			// SSE4 STATS: 3 shuffle, 4 mul, 4 dpps

			__m128 const mul0 = _mm_mul_ps(q1.Data, _mm_shuffle_ps(q2.Data, q2.Data, _MM_SHUFFLE(0, 1, 2, 3)));
			__m128 const mul1 = _mm_mul_ps(q1.Data, _mm_shuffle_ps(q2.Data, q2.Data, _MM_SHUFFLE(1, 0, 3, 2)));
			__m128 const mul2 = _mm_mul_ps(q1.Data, _mm_shuffle_ps(q2.Data, q2.Data, _MM_SHUFFLE(2, 3, 0, 1)));
			__m128 const mul3 = _mm_mul_ps(q1.Data, q2.Data);

#			if GLM_ARCH & GLM_ARCH_SSE41_BIT
				__m128 const add0 = _mm_dp_ps(mul0, _mm_set_ps(1.0f, -1.0f,  1.0f,  1.0f), 0xff);
				__m128 const add1 = _mm_dp_ps(mul1, _mm_set_ps(1.0f,  1.0f,  1.0f, -1.0f), 0xff);
				__m128 const add2 = _mm_dp_ps(mul2, _mm_set_ps(1.0f,  1.0f, -1.0f,  1.0f), 0xff);
				__m128 const add3 = _mm_dp_ps(mul3, _mm_set_ps(1.0f, -1.0f, -1.0f, -1.0f), 0xff);
#			else
				__m128 const mul4 = _mm_mul_ps(mul0, _mm_set_ps(1.0f, -1.0f,  1.0f,  1.0f));
				__m128 const add0 = _mm_add_ps(mul0, _mm_movehl_ps(mul4, mul4));
				__m128 const add4 = _mm_add_ss(add0, _mm_shuffle_ps(add0, add0, 1));

				__m128 const mul5 = _mm_mul_ps(mul1, _mm_set_ps(1.0f,  1.0f,  1.0f, -1.0f));
				__m128 const add1 = _mm_add_ps(mul1, _mm_movehl_ps(mul5, mul5));
				__m128 const add5 = _mm_add_ss(add1, _mm_shuffle_ps(add1, add1, 1));

				__m128 const mul6 = _mm_mul_ps(mul2, _mm_set_ps(1.0f,  1.0f, -1.0f,  1.0f));
				__m128 const add2 = _mm_add_ps(mul6, _mm_movehl_ps(mul6, mul6));
				__m128 const add6 = _mm_add_ss(add2, _mm_shuffle_ps(add2, add2, 1));

				__m128 const mul7 = _mm_mul_ps(mul3, _mm_set_ps(1.0f, -1.0f, -1.0f, -1.0f));
				__m128 const add3 = _mm_add_ps(mul3, _mm_movehl_ps(mul7, mul7));
				__m128 const add7 = _mm_add_ss(add3, _mm_shuffle_ps(add3, add3, 1));
		#endif

			// This SIMD code is a politically correct way of doing this, but in every test I've tried it has been slower than
			// the final code below. I'll keep this here for reference - maybe somebody else can do something better...
			//
			//__m128 xxyy = _mm_shuffle_ps(add4, add5, _MM_SHUFFLE(0, 0, 0, 0));
			//__m128 zzww = _mm_shuffle_ps(add6, add7, _MM_SHUFFLE(0, 0, 0, 0));
			//
			//return _mm_shuffle_ps(xxyy, zzww, _MM_SHUFFLE(2, 0, 2, 0));

			tquat<float, P> Result(uninitialize);
			_mm_store_ss(&Result.x, add4);
			_mm_store_ss(&Result.y, add5);
			_mm_store_ss(&Result.z, add6);
			_mm_store_ss(&Result.w, add7);
			return Result;
		}
	};
*/

	template <precision P>
	struct compute_dot<tquat, float, P, true>
	{
		static GLM_FUNC_QUALIFIER float call(tquat<float, P> const& x, tquat<float, P> const& y)
		{
			return _mm_cvtss_f32(glm_vec1_dot(x.data, y.data));
		}
	};

	template <precision P>
	struct compute_quat_add<float, P, true>
	{
		static tquat<float, P> call(tquat<float, P> const& q, tquat<float, P> const& p)
		{
			tquat<float, P> Result(uninitialize);
			Result.data = _mm_add_ps(q.data, p.data);
			return Result;
		}
	};

#	if GLM_ARCH & GLM_ARCH_AVX_BIT
	template <precision P>
	struct compute_quat_add<double, P, true>
	{
		static tquat<double, P> call(tquat<double, P> const & a, tquat<double, P> const & b)
		{
			tquat<double, P> Result(uninitialize);
			Result.data = _mm256_add_pd(a.data, b.data);
			return Result;
		}
	};
#	endif

	template <precision P>
	struct compute_quat_sub<float, P, true>
	{
		static tquat<float, P> call(tquat<float, P> const& q, tquat<float, P> const& p)
		{
			tvec4<float, P> Result(uninitialize);
			Result.data = _mm_sub_ps(q.data, p.data);
			return Result;
		}
	};

#	if GLM_ARCH & GLM_ARCH_AVX_BIT
	template <precision P>
	struct compute_quat_sub<double, P, true>
	{
		static tquat<double, P> call(tquat<double, P> const & a, tquat<double, P> const & b)
		{
			tquat<double, P> Result(uninitialize);
			Result.data = _mm256_sub_pd(a.data, b.data);
			return Result;
		}
	};
#	endif

	template <precision P>
	struct compute_quat_mul_scalar<float, P, true>
	{
		static tquat<float, P> call(tquat<float, P> const& q, float s)
		{
			tvec4<float, P> Result(uninitialize);
			Result.data = _mm_mul_ps(q.data, _mm_set_ps1(s));
			return Result;
		}
	};

#	if GLM_ARCH & GLM_ARCH_AVX_BIT
	template <precision P>
	struct compute_quat_mul_scalar<double, P, true>
	{
		static tquat<double, P> call(tquat<double, P> const& q, double s)
		{
			tquat<double, P> Result(uninitialize);
			Result.data = _mm256_mul_pd(q.data, _mm_set_ps1(s));
			return Result;
		}
	};
#	endif

	template <precision P>
	struct compute_quat_div_scalar<float, P, true>
	{
		static tquat<float, P> call(tquat<float, P> const& q, float s)
		{
			tvec4<float, P> Result(uninitialize);
			Result.data = _mm_div_ps(q.data, _mm_set_ps1(s));
			return Result;
		}
	};

#	if GLM_ARCH & GLM_ARCH_AVX_BIT
	template <precision P>
	struct compute_quat_div_scalar<double, P, true>
	{
		static tquat<double, P> call(tquat<double, P> const& q, double s)
		{
			tquat<double, P> Result(uninitialize);
			Result.data = _mm256_div_pd(q.data, _mm_set_ps1(s));
			return Result;
		}
	};
#	endif

	template <precision P>
	struct compute_quat_mul_vec4<float, P, true>
	{
		static tvec4<float, P> call(tquat<float, P> const& q, tvec4<float, P> const& v)
		{
			__m128 const q_wwww = _mm_shuffle_ps(q.data, q.data, _MM_SHUFFLE(3, 3, 3, 3));
			__m128 const q_swp0 = _mm_shuffle_ps(q.data, q.data, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 const q_swp1 = _mm_shuffle_ps(q.data, q.data, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 const v_swp0 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 const v_swp1 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 1, 0, 2));
	
			__m128 uv      = _mm_sub_ps(_mm_mul_ps(q_swp0, v_swp1), _mm_mul_ps(q_swp1, v_swp0));
			__m128 uv_swp0 = _mm_shuffle_ps(uv, uv, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 uv_swp1 = _mm_shuffle_ps(uv, uv, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 uuv     = _mm_sub_ps(_mm_mul_ps(q_swp0, uv_swp1), _mm_mul_ps(q_swp1, uv_swp0));

			__m128 const two = _mm_set1_ps(2.0f);
			uv  = _mm_mul_ps(uv, _mm_mul_ps(q_wwww, two));
			uuv = _mm_mul_ps(uuv, two);

			tvec4<float, P> Result(uninitialize);
			Result.data = _mm_add_ps(v.Data, _mm_add_ps(uv, uuv));
			return Result;
		}
	};
}//namespace detail
}//namespace glm

#endif//GLM_ARCH & GLM_ARCH_SSE2_BIT

// CG_REVISION 5076130387d5a9915bfcd693bb4e6b142e11aa30
