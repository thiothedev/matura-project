#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glew.h>

#include "../Utils/File.h"
#include "../Utils/Image.h"

/**
 * Represents a Vertex Array Object
*/
typedef struct VAO
{
  GLuint ID;
} VAO;

/**
 * Represents a Vertex Buffer Object.
*/
typedef struct VBO
{
  GLuint ID;
} VBO;

/**
 * Represents an Element Buffer Object
*/
typedef struct EBO
{
  GLuint ID;
} EBO;

/**
 * Initializes a Vertex Array Object (VAO) with the provided VAO object.
 * 
 * @param VAO The VAO object to be initialized.
 */
void dp_initVAO(VAO* VAO);
/**
 * Binds the specified VAO object for rendering.
 * 
 * @param VAO The VAO object to be bound.
 */
void dp_bindVAO(VAO* VAO);
/**
 * Links vertex attribute data to the specified VBO (Vertex Buffer Object) within a VAO.
 * 
 * @param VBO     The VBO object containing the vertex attribute data.
 * @param layout  The attribute layout index.
 * @param size    The number of components per attribute (e.g., 2 for 2D, 3 for 3D).
 * @param type    The data type of each component.
 * @param stride  The stride between consecutive attributes.
 * @param offset  The offset of the attribute data within the VBO.
 */
void dp_linkAttrib(VBO* VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset);
/**
 * Unbinds the currently bound VAO.
 */
void dp_unbindVAO();
/**
 * Deletes the specified VAO object and releases associated resources.
 * 
 * @param VAO The VAO object to be deleted.
 */
void dp_deleteVAO(VAO* VAO);

/**
 * Initializes a Vertex Buffer Object (VBO) with the provided vertices and size.
 * 
 * @param VBO       The VBO object to be initialized.
 * @param vertices  The array of vertex data.
 * @param size      The size of the vertex data in bytes.
 */
void dp_initVBO(VBO* VBO, GLfloat vertices[], GLsizeiptr size);
/**
 * Binds the specified VBO object for rendering.
 *
 * @param VBO The VBO object to be bound.
 */
void dp_bindVBO(VBO* VBO);
/**
 * Unbinds the currently bound VBO.
 */
void dp_unbindVBO();
/**
 * Deletes the specified VBO object and releases associated resources.
 *
 * @param VBO The VBO object to be deleted.
 */
void dp_deleteVBO(VBO* VBO);

/**
 * Initializes an Element Buffer Object (EBO) with the provided indices and size.
 *
 * @param EBO      The EBO object to be initialized.
 * @param indices  The array of indices.
 * @param size     The size of the index data in bytes.
 */
void dp_initEBO(EBO* EBO, GLuint indices[], GLsizeiptr size);
/**
 * Binds the specified EBO object for rendering.
 *
 * @param EBO The EBO object to be bound.
 */
void dp_bindEBO(EBO* EBO);
/**
 * Unbinds the currently bound EBO.
 */
void dp_unbindEBO();
/**
 * Unbinds the currently bound EBO.
 */
void dp_deleteEBO(EBO* EBO);

/**
 * Represents a Shader program.
 */
typedef struct Shader
{
  GLuint ID;
} Shader;

/**
 * Initializes a Shader object with the provided vertex and fragment shader source code paths.
 *
 * @param shader            The Shader object to be initialized.
 * @param vertexSourcePath  The file path to the vertex shader source code.
 * @param fragmentSourcePath The file path to the fragment shader source code.
 */
void dp_initShader(Shader* Shader, const char* vertexSourcePath, const char* fragmentSourcePath);
/**
 * Sets the specified Shader object as the current active shader program.
 *
 * @param shader The Shader object to be used.
 */
void dp_useShader(Shader* Shader);
/**
 * Deletes the specified Shader object and releases associated resources.
 *
 * @param shader The Shader object to be deleted.
 */
void dp_deleteShader(Shader* Shader);

/**
 * Represents a texture object in OpenGL.
 */
typedef struct Texture
{
  GLuint ID;
  GLenum type;
} Texture;

/**
 * Initializes a texture object with the specified parameters.
 * 
 * @param texture Pointer to the Texture struct to be initialized.
 * @param path Path to the image file to be used as the texture.
 * @param texType Type of the texture (e.g., GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP, etc.).
 * @param slot Texture slot or unit to bind the texture to.
 * @param format Format of the texture data (e.g., GL_RGBA, GL_RGB, etc.).
 * @param pixelType Type of the pixel data (e.g., GL_UNSIGNED_BYTE, GL_FLOAT, etc.).
 */
void dp_initTexture(Texture* texture, const char* path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
/**
* Sets the texture unit of a shader uniform variable to the specified texture unit.
*
* @param shader Pointer to the Shader struct representing the shader program.
* @param uniform Name of the uniform variable in the shader.
* @param unit Texture unit to be bound to the uniform variable.
*/
void dp_textureUnit(Shader* shader, const char* uniform, GLuint unit);
/**
 * Binds a texture object for rendering.
 *
 * @param texture Pointer to the Texture struct representing the texture object.
 */
void dp_bindTexture(Texture* texture);
/**
 * Unbinds a texture object.
 *
 * @param texture Pointer to the Texture struct representing the texture object.
 */
void dp_unbindTexture(Texture* texture);
/**
 * Deletes a texture object and frees any associated resources.
 *
 * @param texture Pointer to the Texture struct representing the texture object.
 */
void dp_deleteTexture(Texture* texture);

#endif // GRAPHICS_H
