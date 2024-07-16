#include <ROUGE2.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class ExLayer : public ROUGE2::Layer {
public:
	ExLayer() : Layer("Example"), m_CamController(1280.0f / 720.0f, true)
	{
		m_VertexArray.reset(ROUGE2::VertexArray::Create());

		float vertices[3 * 7] = {
			//----------pos---------/------col--------
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.0f, 0.2f, 1.0f
		};
		/*
			small aside : in the future when importing blender models it will be oriented 90 degrees counter-clockwise from its original rotation
			as it operates on X, Z, Y basis.
		*/

		
		ROUGE2::Ref<ROUGE2::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ROUGE2::VertexBuffer::Create(vertices, sizeof(vertices)));

		ROUGE2::BufferLayout layout = {
			{ ROUGE2::ShaderDataType::Vec3, "a_Position" },
			{ ROUGE2::ShaderDataType::Vec4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout); //always set layout before adding vertex buffer to vertarray
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		ROUGE2::Ref<ROUGE2::IndexBuffer> indexBuffer;
		indexBuffer.reset(ROUGE2::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA.reset(ROUGE2::VertexArray::Create());


		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		ROUGE2::Ref<ROUGE2::VertexBuffer> squareVB;
		squareVB.reset(ROUGE2::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ROUGE2::ShaderDataType::Vec3, "a_Position" },
			{ ROUGE2::ShaderDataType::Vec2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ROUGE2::Ref<ROUGE2::IndexBuffer> squareIB;
		squareIB.reset(ROUGE2::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec3 v_Position;
			out vec4 v_Color;
			
			uniform mat4 u_ViewProj;
			uniform mat4 u_Transform;

			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);
				
			}			


		)"; //dont judge this is temporary testing

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 col;
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				col = vec4(v_Position + 0.5, 1.0);
				col = v_Color;
				
			}			
		)";

		m_Shader = ROUGE2::Shader::Create("VertColTriangle", vertexSrc, fragmentSrc);

		std::string FlatColVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			uniform mat4 u_ViewProj;
			uniform mat4 u_Transform;


			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string FlatColFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
		
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_Shader2 = ROUGE2::Shader::Create("FlatCol", FlatColVertexSrc, FlatColFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/texture.glsl");

		m_TestBGTex = (ROUGE2::Texture2D::Create("assets/textures/Checkerboard.png"));

		m_Texture = (ROUGE2::Texture2D::Create("assets/textures/ROUGE.png"));

		std::dynamic_pointer_cast<ROUGE2::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<ROUGE2::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(ROUGE2::Timestep ts) override{
		m_CamController.OnUpdate(ts);

		R2_TRACE("Delta Time: {0} seconds o/ ({1} ms)", ts.GetSeconds(), ts.GetMilliseconds());

		ROUGE2::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ROUGE2::RenderCommand::Clear();

		ROUGE2::Renderer::BeginScene(m_CamController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ROUGE2::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<ROUGE2::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				ROUGE2::Renderer::Submit(m_Shader2, m_SquareVA, transform);
				
			}
		}

		auto textureShader = m_ShaderLibrary.Get("texture");

		m_TestBGTex->Bind();
		ROUGE2::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_Texture->Bind();
		ROUGE2::Renderer::Submit(textureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), logoVec) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//ROUGE2::Renderer::Submit(m_Shader, m_VertexArray);

		ROUGE2::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(ROUGE2::Event& e) override {
		m_CamController.OnEvent(e);
	}


private:
	ROUGE2::ShaderLibrary m_ShaderLibrary;
	ROUGE2::Ref<ROUGE2::Shader> m_Shader;
	ROUGE2::Ref<ROUGE2::VertexArray> m_VertexArray;

	ROUGE2::Ref<ROUGE2::Texture2D> m_Texture, m_TestBGTex;

	ROUGE2::Ref<ROUGE2::Shader> m_Shader2;
	ROUGE2::Ref<ROUGE2::VertexArray> m_SquareVA;

	ROUGE2::OrthographicCameraController m_CamController;
	glm::vec3 m_CamPos;


	glm::vec3 m_SquareColor = { 0.6f, 0.2f, 0.2f };
	glm::vec3 logoVec = { 0.25f, -0.25f, 0.0f };
};



class Sandbox : public ROUGE2::Application {
public:
	Sandbox() {
		PushLayer(new ExLayer());
	}

	~Sandbox() {
		
	}
};

ROUGE2::Application* ROUGE2::CreateApplication() {
	return new Sandbox(); //ret. application to entrypoint.h
}