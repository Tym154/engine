#include <renderer/loaders/obj_loader.h>

Mesh Obj_loader::load_obj(const char* filename) {
    Mesh mesh;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << filename << std::endl;
        return mesh;
    }

    std::vector<Vertex> temp_vertices;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {  // vertex
            float x, y, z;
            iss >> x >> y >> z;
            temp_vertices.push_back(Vertex(x, y, z));
        } 
        else if (prefix == "f") {  // face
            std::string vert_str[3];
            iss >> vert_str[0] >> vert_str[1] >> vert_str[2];

            Vertex verts[3];
            for (int i = 0; i < 3; i++) {
                std::string index_str = vert_str[i];
                // If there is a '/', take only the first number (vertex index)
                size_t slash_pos = index_str.find('/');
                if (slash_pos != std::string::npos) {
                    index_str = index_str.substr(0, slash_pos);
                }
                int vi = std::stoi(index_str);
                verts[i] = temp_vertices[vi - 1]; // OBJ indices start at 1
            }

            mesh.faces.push_back(Face(verts[0], verts[1], verts[2], Color()));
        }
    }

    file.close();

    return mesh;
}