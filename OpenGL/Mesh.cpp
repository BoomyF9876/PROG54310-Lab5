#include "Mesh.h"

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);

    delete diffuseTexture;
    delete specularTexture;
}

void Mesh::Create(Shader* _shader)
{
    shader = _shader;

    diffuseTexture = new Texture();
    diffuseTexture->LoadTexture("../Assets/Textures/MetalFrameWood.jpg");

    specularTexture = new Texture();
    specularTexture->LoadTexture("../Assets/Textures/MetalFrame.jpg");

    vertexData = {
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    //vertexData = {
    //    //50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    //    //50.0f, -50.0f, 0.0f, 1.0f, 0.549f, 0.0f, 1.0f, 0.0f,
    //    //-50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    //    //-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    //    -50.0f, -50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    //    50.0f, -50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    //    50.0f, 50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    //    50.0f, 50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    //    -50.0f, 50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    //    -50.0f, -50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    //    -50.0f, -50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //    50.0f, -50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    //    50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    //    50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    //    -50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    //    -50.0f, -50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //    -50.0f, 50.0f, 50.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //    -50.0f, 50.0f, -50.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    //    -50.0f, -50.0f, -50.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //    -50.0f, -50.0f, -50.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //    -50.0f, -50.0f, 50.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    //    -50.0f, 50.0f, 50.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //    50.0f, 50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //    50.0f, 50.0f, -50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    //    50.0f, -50.0f, -50.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //    50.0f, -50.0f, -50.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //    50.0f, -50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    //    50.0f, 50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //    -50.0f, -50.0f, -50.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    //    50.0f, -50.0f, -50.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    //    50.0f, -50.0f, 50.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    //    50.0f, -50.0f, 50.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    //    -50.0f, -50.0f, 50.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    //    -50.0f, -50.0f, -50.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    //    -50.0f, 50.0f, -50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    //    50.0f, 50.0f, -50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    //    50.0f, 50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    //    50.0f, 50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    //    -50.0f, 50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    //    -50.0f, 50.0f, -50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    //};

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    //indexData = {
    //    2,0,3,2,1,0
    //};

    //glGenBuffers(1, &indexBuffer);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);
}

void Mesh::BindAttributes()
{
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );

    //glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    /*glEnableVertexAttribArray(shader -> GetAttrColors());
    glVertexAttribPointer(
        shader->GetAttrColors(),
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );*/

    glEnableVertexAttribArray(shader->GetAttrNormals());
    glVertexAttribPointer(
        shader->GetAttrNormals(),
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(shader->GetAttrTexCoords());
    glVertexAttribPointer(
        shader->GetAttrTexCoords(),
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );

    glVertexAttrib2fv(shader->GetAttrTexTranslation(), glm::value_ptr(texTranslation));

    /*glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1->GetTexture());
    glUniform1i(shader->GetTexSampler1(), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2->GetTexture());
    glUniform1i(shader->GetTexSampler2(), 1);*/
}

void Mesh::SetShaderVariables(glm::mat4 _pv, const std::list<Mesh*>& _lights)
{
    shader->SetMat4("World", world);
    shader->SetMat4("WVP", _pv * world);
    shader->SetVec3("CameraPosition", cameraPosition);

    int i = 0;
    for (auto& light : _lights)
    {
        shader->SetVec3(Concat("light[", i, "].position").c_str(), light->GetPosition());
        shader->SetVec3(Concat("light[", i, "].direction").c_str(), light->GetLightDirection());

        shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 0.1f, 0.1f, 0.1f });
        shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), light->GetLightColor());
        shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), {3.0f, 3.0f, 3.0f});

        shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
        shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.045f);
        shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.0075f);

        //shader->SetVec3("light.color", lightColor);
        shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(45.0f));
        shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 100);
    
        i++;
    }

    shader->SetFloat("material.specularStrength", 8.0f);
    shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, diffuseTexture->GetTexture());
    shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, specularTexture->GetTexture());
}

void Mesh::CalculateTransform()
{
    world = glm::translate(glm::mat4(1.0f), position);
    world = glm::rotate(world, rotation.y, glm::vec3(0, 1, 0));
    world = glm::rotate(world, rotation.x, glm::vec3(1, 0, 0));
    world = glm::rotate(world, rotation.z, glm::vec3(0, 0, 1));
    world = glm::scale(world, scale);
}

void Mesh::Render(glm::mat4 _wvp, const std::list<Mesh*>& _lights)
{
    glUseProgram(shader->GetProgramID());

    CalculateTransform();
    SetShaderVariables(_wvp, _lights);
    BindAttributes();
    
    glDrawArrays(GL_TRIANGLES, 0, vertexData.size()/8);

    glDisableVertexAttribArray(shader->GetAttrVertices());
    //glDisableVertexAttribArray(shader->GetAttrColors());
    glDisableVertexAttribArray(shader->GetAttrNormals());
    glDisableVertexAttribArray(shader->GetAttrTexCoords());
    glDisableVertexAttribArray(shader->GetAttrTexTranslation());
}

void Mesh::RotateWorld(float _angle, glm::vec3 axis)
{
    world = glm::rotate(world, _angle, axis);
}

void Mesh::MoveTexture(float _dx, float _dy)
{
    texTranslation += glm::vec2(_dx, _dy);
}

std::string Mesh::Concat(const std::string& _s1, int _index, const std::string& _s2)
{
    std::string index = std::to_string(_index);
    return (_s1 + index + _s2);
}