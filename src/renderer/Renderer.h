#pragma once

#include <scene/Scene.h>
#include <utils/collection/Color.h>

void Render(VertexArray vertexArray, Shader shader);
void ClearFrame(Color24 color);