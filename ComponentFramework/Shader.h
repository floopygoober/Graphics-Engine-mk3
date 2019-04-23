#ifndef SHADER_H
#define SHADER_H

class Shader {
public:
	Shader(const Shader&) = delete;
	Shader(Shader&&) = delete;
	Shader& operator = (const Shader&) = delete;
	Shader& operator = (Shader&&) = delete;

	Shader(const char *vsFilename, const char *fsFilename, int numAttributes,...);
	~Shader();
	unsigned int getProgram() const;
private:	
	char* readTextFile(const char *fileName);	
	void readCompileAttach(const char *vsFilename, const char *fsFilename);
	void link();

	void exploreUniforms();

	unsigned int shader;
	unsigned int vertShader;
	unsigned int fragShader;
};


#endif