#pragma once

#include <scene/Scene.h>
#include <utils/collection/Color.h>

void render(VertexArray vertexArray, Shader shader);
void clearFrame(Color24 color);