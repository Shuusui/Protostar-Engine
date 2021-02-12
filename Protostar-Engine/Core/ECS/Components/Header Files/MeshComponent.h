#pragma once
#include "BaseComponent.h"
#include "Guid.h"

namespace Protostar
{
	namespace JsonKeys
	{
		constexpr const char* JSONMESHCOMPGUID				= "guid";
		constexpr const char* JSONMESHCOMPMODELGUID			= "model_guid";
	}

	class CMeshComponent : public CBaseComponent
	{
	public:
		CMeshComponent()
			:CBaseComponent("Mesh Component", Json())
			, m_guid(SGuid::NewGuid())
			, m_modelGuid(SGuid())
		{

		}

		CMeshComponent(const Json& _json)
			:CBaseComponent("Mesh Component", _json)
		{
			using namespace JsonKeys;
			m_jsonObject = _json;
			m_guid = m_jsonObject[JSONMESHCOMPGUID].get<std::string>();
			m_modelGuid = m_jsonObject[JSONMESHCOMPMODELGUID].get<std::string>();
		}

		virtual void OnSave() override
		{
			using namespace JsonKeys;
			m_jsonObject =
			{
				{JSONMESHCOMPGUID, m_guid.ToString()},
				{JSONMESHCOMPMODELGUID, m_modelGuid.ToString()}
			};
		}

		SGuid GetGuid() const
		{
			return m_guid;
		}

		SGuid GetModelGuid() const
		{
			return m_modelGuid;
		}

		void SetGuid(const SGuid& _guid)
		{
			m_guid = _guid;
		}

		void SetModelGuid(const SGuid& _guid)
		{
			m_modelGuid = _guid;
		}

	private:
		SGuid m_guid;
		SGuid m_modelGuid;
	};
}

#undef JSONMESHCOMPGUID
#undef JSONMESHCOMPMODELGUID