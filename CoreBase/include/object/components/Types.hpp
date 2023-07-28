#pragma once

namespace CubA4::object
{
	enum class ComponentType
	{
		// position, required
		GlobalPosition,
		// id world, id dimension, id chunk, id entity, required
		WorldInfo,
		Controllable, // ? custom ?
		/// If present in entity - then it controls loaded and active chunks
		/// Should be parameterized (std::max(localChunkFar, remoteChunkFar))
		Observer,
		/// Conrtrols active chunks
		Anchor,
		/// Can play the sound
		SoundControl,
		Collider,
		Physics
	};
}