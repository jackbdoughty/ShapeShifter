#pragma once

#include "../va/va.h"
#include "../ib/ib.h"
#include "../shader/shader.h"

class Renderer {
public:
	static void clearBuffer() ;
	static void drawElements(const VertexArray&, const IndexBuffer&, const Shader&) ;
};