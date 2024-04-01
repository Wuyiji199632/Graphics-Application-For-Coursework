#include "Mesh.h"

#define TINYOBJECTLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>
Mesh::Mesh(const wchar_t* full_path):Resource(full_path)
{

    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    std::string inputFile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path);

   bool res= tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputFile.c_str());

   if (!err.empty()||!res|| shapes.size() > 1) {

       throw std::exception("Mesh not created successfully");
   }

 

   for (size_t s = 0; s < shapes.size(); s++) {

       for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size();f++) {

           int num_face_verts = shapes[s].mesh.num_face_vertices[f];

       }
   }
}

Mesh::~Mesh()
{
}

const VertexBufferPtr& Mesh::getVertexBuffer()
{
    // TODO: insert return statement here
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
    // TODO: insert return statement here
}
