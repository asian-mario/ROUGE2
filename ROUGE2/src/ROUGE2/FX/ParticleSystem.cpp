#include "r2pch.h"
#include "ParticleSystem.h"

#include "Random.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>


namespace ROUGE2 {
	ParticleSystem::ParticleSystem(){
		m_ParticlePool.resize(1000);
	}

	void ParticleSystem::Emit(const ParticleProps& particleProps){
		Particle& particle = m_ParticlePool[m_PoolIndex];
		particle.Active = true;
		particle.Position = particleProps.Position;
		particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

		//Particle Velocity:
		particle.Velocity = particleProps.Velocity;
		particle.Velocity.x += particleProps.velocityVariation.x * (Random::Float() - 0.5f);
		particle.Velocity.y += particleProps.velocityVariation.y * (Random::Float() - 0.5f);

		//Particle Color:
		particle.ColorBegin = particleProps.ColorBegin;
		particle.ColorEnd = particleProps.ColorEnd;

		//Particle Size:
		particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * (Random::Float() - 0.5f);
		particle.sizeEnd = particleProps.sizeEnd;

		//Particle Lifetime:
		particle.LifeTime = particleProps.LifeTime;
		particle.LifeRemaining = particleProps.LifeTime;

		m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
	}

	void ParticleSystem::OnUpdate(Timestep ts){
		for (auto& particle : m_ParticlePool) {
			if (!particle.Active)
				continue;
			if (particle.LifeRemaining <= 0.0f) {
				particle.Active = false;
				continue;
			}

			particle.LifeRemaining -= ts;
			particle.Position += particle.Velocity * (float)ts;
			particle.Rotation += 0.01f * ts;

		}
	}

	void ParticleSystem::OnRender(){
		for (auto& particle : m_ParticlePool) {
			if (!particle.Active)
				continue;

			float life = particle.LifeRemaining / particle.LifeTime;
			glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
			color.a = color.a * life;

			float size = glm::lerp(particle.sizeEnd, particle.sizeBegin, life);
			Renderer2D::DrawRotQuad(particle.Position, { size, size }, particle.Rotation, color);
		}
	}
}