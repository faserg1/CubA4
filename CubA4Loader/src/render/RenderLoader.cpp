#include "RenderLoader.hpp"
#include <boost/dll.hpp>
#include <map>
#include <stdexcept>

using namespace CubA4::render;

struct RenderLoader::Private
{
	std::map<IRenderInfo *, boost::dll::shared_library> renderLibraries;
	boost::dll::shared_library currentLibrary;
};

RenderLoader::RenderLoader(std::string renderPath) :
	importSymbolName_("getRenderInfo"),
	currentRenderInfo_(nullptr)
{
	data_ = std::make_shared<RenderLoader::Private>();
	using namespace boost::filesystem;
	path rednerFolder = path(renderPath);
	recursive_directory_iterator renderFolderIterator(rednerFolder), end;

	std::vector<path> renderCandidates;

	for (renderFolderIterator; renderFolderIterator != end; renderFolderIterator++)
	{
		auto path = renderFolderIterator->path();
		if (is_directory(path))
			continue;
		if (path.extension() != boost::dll::shared_library::suffix())
			continue;
		renderCandidates.push_back(path);
	}

	for (auto candidate : renderCandidates)
	{
		boost::dll::shared_library library(candidate);
		if (!library.is_loaded())
		{
			//todo: вывести ошибку
			continue;
		}
		if (!library.has(importSymbolName_))
		{
			//todo: вывести ошибку
			library.unload();
			continue;
		}
		auto getRenderInfo = library.get<IRenderInfo *()>(importSymbolName_);
		auto renderInfo = getRenderInfo();
		data_->renderLibraries.insert(std::make_pair(renderInfo, library));
	}
}

RenderLoader::~RenderLoader()
{
}

std::vector<IRenderInfo*> RenderLoader::getRenderInfoCollection()
{
	std::vector<IRenderInfo*> ri;
	for (auto pair : data_->renderLibraries)
	{
		ri.push_back(pair.first);
	}
	return ri;
}

void RenderLoader::setCurrentRenderInfo(IRenderInfo *renderInfo)
{
	//data_->renderLibraries.clear();
	if (currentRenderInfo_)
		throw std::runtime_error("Shut the fuck up!");
	currentRenderInfo_ = renderInfo;
	//TODO:
	//Проверить, не выбрана ли уже библиотека рендеринга
	//Если выбрана, выбросить ошибку
	//
	//Выгрузить все остальные ненужные библиотеки.
	//Сохранить нужную библиотеку.
	//Словарь можно очистить
}

IRenderInfo *RenderLoader::getCurrentRenderInfo()
{
	return currentRenderInfo_;
}
