#include "stdafx.h"
#include "SelectUpCommand.h"

#include <utility>

#include "GameObject.h"
#include "SelectComponent.h"

SelectUpCommand::SelectUpCommand(std::weak_ptr<StreamEngine::GameObject> object)
	:m_SelectBoardObject(std::move(object))
{
}

void SelectUpCommand::Execute()
{
	std::shared_ptr<SelectComponent> selectComp{ m_SelectBoardObject.lock()->GetComponent<SelectComponent>() };
	if (selectComp != nullptr)
	{
		selectComp->SetSelected(selectComp->GetSelected() - 1);
	}
}
