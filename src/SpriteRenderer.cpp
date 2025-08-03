#include "SpriteRenderer.h"
#include <iostream>

SpriteRenderer::SpriteRenderer(const Shader& shader)
{
    this->shader = shader;
    initRenderData();
}

void SpriteRenderer::initRenderData()
{
	unsigned int VBO;
    unsigned int COLOR_VBO;
    // float vertices[] = {
    //     // pos      // tex
    //     0.0f, 1.0f, 0.0f, 1.0f, // first four attributes (position coordinates, texture coordinates)
    //     1.0f, 0.0f, 1.0f, 0.0f, // next four
    //     0.0f, 0.0f, 0.0f, 0.0f, // and so ..on

    //     0.0f, 1.0f, 0.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f, 1.0f,
    //     1.0f, 0.0f, 1.0f, 0.0f
    // };

    float vertices[] = {
        // pos      // tex
        -0.5f, 0.5f,     0.0f, 1.0f, // first four attributes (position coordinates, texture coordinates)
        0.5f, -0.5f,     1.0f, 0.0f, // next four
        -0.5f, -0.5f,    0.0f, 0.0f, // and so ..on

        0.5f, -0.5f,    1.0f, 0.0f,
        0.5f, 0.5f,     1.0f, 1.0f,
        -0.5f, 0.5f,    0.0f, 1.0f
    };


    // hardcoded colors for default drawing and stuff
    float colors[] = {
        1.0f, 0.0f, 0.0f,   // Red
        0.0f, 1.0f, 0.0f,   // Green
        0.0f, 0.0f, 1.0f,   // Blue

        0.0f, 1.0f, 0.0f,   // Green (shared vertex)
        0.0f, 0.0f, 1.0f,   // Blue 
        1.0f, 0.0f, 0.0f    // Red (shared vertex)
    };

    glGenVertexArrays(1, &this->quadVAO);
    glBindVertexArray(this->quadVAO);
    
    glGenBuffers(1, &VBO);
    // bind VBO buffer to GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // transfer data to the bound(VBO) using the currently bound GL_ARRAY_BUFFER 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    // separately assign color data
    // only for debug mode
    glBindBuffer(GL_VERTEX_ARRAY, 0);
    glGenBuffers(1, &COLOR_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, COLOR_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    // in the current VAO 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    //unbind current VBO and VAO 
    glBindBuffer(GL_VERTEX_ARRAY, 0);
    glBindVertexArray(0);
    // no we can always use this->quadVAO to refer to this object's data 
}

void SpriteRenderer::DrawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
    //prepare transformation
    this->shader.Use();
    
    //Remember the following transformations will take place in the reverse order 
    //because these matrices are col major so the transform operation reverses the whole operation order
    //So if you wanna understand step by step transform then read from the bottom to up
    glm::mat4 model = glm::mat4(1.0f);
    //Remember: OPERATION APPLIED FIRST IS WRITTEN LAST or CLOSER TO THE VECTOR
    model = glm::translate(model, glm::vec3(position, 0.0f));

    // remember that the author used defined vertex coords in the top left quadrant,
    // leaving (0,0)(origin) as the bottom right corner 
    // model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 
    // model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    // std::cout << "scaling factor: " << size.x << " " << size.y << std::endl; 
    model = glm::scale(model, glm::vec3(size, 1.0f));
    // model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));

    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", glm::vec3(1.0f));

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawDebug(Texture2D texture) {
    //prepare transformation
    this->shader.Use();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
    
    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", glm::vec3(1.0f));

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
