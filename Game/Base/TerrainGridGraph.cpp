#include "TerrainGridGraph.h"

#include "TerrainGraphNode.h"


using namespace Game::AI;


TerrainGridGraph::TerrainGridGraph(const glm::vec2& position, int columns, int rows, const glm::ivec2& cellSize,
	bool isDirectionalGraph, bool isConnectedDiagonally, float costStraight, float costDiagonally) :

	bae::Graphs::GridGraph(position, columns, rows, cellSize, isDirectionalGraph, isConnectedDiagonally, costStraight,
		costDiagonally)
{

}


void TerrainGridGraph::SetNodeTerrainType(int nodeId, TerrainType type) const
{
	//TerrainGraphNode* const pNode = reinterpret_cast<TerrainGraphNode*>(GetNode(nodeId));
	TerrainGraphNode* const pNode = dynamic_cast<TerrainGraphNode*>(GetNode(nodeId));
	if (pNode)
		pNode->SetTerrainType(type);

}


