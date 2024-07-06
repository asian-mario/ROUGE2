#include <ROUGE2.h>
#include "imgui/imgui.h"

class ExLayer : public ROUGE2::Layer {
public:
	ExLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CamPos(0.0f, 0.0f, 0.0f)
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

		std::shared_ptr<ROUGE2::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ROUGE2::VertexBuffer::Create(vertices, sizeof(vertices)));

		ROUGE2::BufferLayout layout = {
			{ ROUGE2::ShaderDataType::Vec3, "a_Position" },
			{ ROUGE2::ShaderDataType::Vec4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout); //always set layout before adding vertex buffer to vertarray
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<ROUGE2::IndexBuffer> indexBuffer;
		indexBuffer.reset(ROUGE2::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		uint32_t index = 0;
		m_SquareVA.reset(ROUGE2::VertexArray::Create());


		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<ROUGE2::VertexBuffer> squareVB;
		squareVB.reset(ROUGE2::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ROUGE2::ShaderDataType::Vec3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<ROUGE2::IndexBuffer> squareIB;
		squareIB.reset(ROUGE2::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec3 v_Position;
			out vec4 v_Color;
			
			uniform mat4 u_ViewProj;
			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProj * vec4(a_Position, 1.0);
				
			}			


		)"; //dont judge this is temporary testing

		std::string fragmentSrc = R"(
			#version 330
			
			layout(location = 0) out vec4 col;
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				col = vec4(v_Position + 0.5, 1.0);
				col = v_Color;
				
			}			


		)";

		m_Shader.reset(new ROUGE2::Shader(vertexSrc, fragmentSrc));

		std::string Shader2VertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			uniform mat4 u_ViewProj;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProj * vec4(a_Position, 1.0);	
			}
		)";

		std::string Shader2FragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.2, 0.2, 1.0);
			}
		)";

		m_Shader2.reset(new ROUGE2::Shader(Shader2VertexSrc, Shader2FragmentSrc));
	}

	void OnUpdate() override{
		if (ROUGE2::Input::IsKeyPressed(R2_KEY_LEFT)) {
			m_CamPos.x -= m_CamMoveSpeed;
		}
		else if (ROUGE2::Input::IsKeyPressed(R2_KEY_RIGHT)) {
			m_CamPos.x += m_CamMoveSpeed;
		}
		if (ROUGE2::Input::IsKeyPressed(R2_KEY_UP)) {
			m_CamPos.y += m_CamMoveSpeed;
		}
		else if (ROUGE2::Input::IsKeyPressed(R2_KEY_DOWN)) {
			m_CamPos.y -= m_CamMoveSpeed;
		}

		if (ROUGE2::Input::IsKeyPressed(R2_KEY_A)) {
			m_CamRot += m_CamRotSpeed;
		}
		if (ROUGE2::Input::IsKeyPressed(R2_KEY_D)) {
			m_CamRot -= m_CamRotSpeed;
		}

		ROUGE2::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ROUGE2::RenderCommand::Clear();

		m_Camera.SetPosition(m_CamPos);
		m_Camera.SetRotation(m_CamRot);

		ROUGE2::Renderer::BeginScene(m_Camera);

		ROUGE2::Renderer::Submit(m_Shader2, m_SquareVA);
		ROUGE2::Renderer::Submit(m_Shader, m_VertexArray);

		ROUGE2::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(ROUGE2::Event& event) override {

	}


private:
	std::shared_ptr<ROUGE2::Shader> m_Shader;
	std::shared_ptr<ROUGE2::VertexArray> m_VertexArray;

	std::shared_ptr<ROUGE2::Shader> m_Shader2;
	std::shared_ptr<ROUGE2::VertexArray> m_SquareVA;

	ROUGE2::OrthoCamera m_Camera;
	glm::vec3 m_CamPos;
	float m_CamRot = 0.0f;
	float m_CamMoveSpeed = 0.1f;
	float m_CamRotSpeed = 1.0f;
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