/// @ref core
/// @file glm/mat2x3.hpp

#pragma once

#include "detail/type_mat2x3.hpp"

namespace glm
{
	/// 2 columns of 3 components matrix of low precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef tmat2x3<float, lowp>		lowp_mat2x3;

	/// 2 columns of 3 components matrix of medium precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef tmat2x3<float, mediump>		mediump_mat2x3;

	/// 2 columns of 3 components matrix of high precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef tmat2x3<float, highp>		highp_mat2x3;

}//namespace glm

// CG_REVISION 68a09862e9435b9f20eb0c0c2aba09327a0eba71
