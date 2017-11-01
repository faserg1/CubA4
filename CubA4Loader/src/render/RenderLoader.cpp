#include "RenderLoader.hpp"
#include <boost/dll.hpp>
#include <map>

using namespace CubA4::render;

struct RenderLoader::Private
{
	std::map<RenderInfo *, boost::dll::shared_library> renderLibraries;
	boost::dll::shared_library currentLibrary;
};

RenderLoader::RenderLoader() :
	importSymbolName("getRenderInfo"),
	data_(nullptr),
	currentRenderInfo_(nullptr)
{
	data_ = new Private;
	using namespace boost::filesystem;
	path rednerFolder = current_path() / "render";
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
			//todo: ������� ������
			continue;
		}
		if (!library.has(importSymbolName))
		{
			//todo: ������� ������
			library.unload();
			continue;
		}
		auto symbolLoad = library.get<RenderInfo *()>(importSymbolName);
		auto renderInfo = symbolLoad();
		data_->renderLibraries.insert(std::make_pair(renderInfo, library));
	}
}

RenderLoader::~RenderLoader()
{
	delete data_;
}

std::vector<RenderInfo*> CubA4::render::RenderLoader::getRenderInfoCollection()
{
	std::vector<RenderInfo*> ri;
	for (auto pair : data_->renderLibraries)
	{
		ri.push_back(pair.first);
	}
	return ri;
}

void CubA4::render::RenderLoader::setCurrentRenderInfo(RenderInfo *renderInfo)
{
	//TODO:
	//���������, �� ������� �� ��� ���������� ����������
	//���� �������, ��������� ������
	//
	//��������� ��� ��������� �������� ����������.
	//��������� ������ ����������.
	//������� ����� ��������
}

RenderInfo * CubA4::render::RenderLoader::getCurrentRenderInfo()
{
	return currentRenderInfo_;
}
