
#ifndef ChunkManager_hpp
#define ChunkManager_hpp

#include <stdio.h>
#include <array>
#include <map>
#include <unordered_map>
#include <pthread.h>

#include "VectorXZ.hpp"
#include "VectorXYZ.hpp"

#include "NonCopyable.hpp"
#include "Chunk.hpp"
#include "WorldMapGenerator.hpp"

namespace GLL {
    
    class World;
    class ChunkRender;
    class Camera;
    
    class ChunkManager  {
        friend World;
    public:
        ChunkManager();
        ~ChunkManager();
        // 获取某个block，如果还没有创建，则会返回nullptr
        std::shared_ptr<ChunkBlock> getBlock(int x,int y,int z);
        std::vector<std::shared_ptr<ChunkBlock>> getBlocks();
        void travesingBlocks(std::function<void(std::shared_ptr<ChunkBlock>)> callback);
        void traviesingChunks(std::function<void(std::shared_ptr<Chunk>)> callback);
        
    private:
        
        // chunk容器，key是对应的坐标，value是chunk对象
        std::mutex chunkMapMutex;
        std::unordered_map<VectorXZ, std::shared_ptr<Chunk>> chunkMap;
        
        // blocks容器
        std::mutex blocksMutex;
        std::vector<std::shared_ptr<ChunkBlock>> blocks;
        // others
        WorldMapGenerator worldGenerator;
        
    private:
        bool loadChunk(int x, int z);
        void unloadChunk(int x, int z);
        void updateNeedRenderChunks(Camera* camera);
        
        bool chunkExistAt(int x, int z);
        bool chunkHasLoadedAt(int x, int z);
        unsigned int getChunksCount();
        
        WorldMapGenerator& getWorldGenerator();
        std::shared_ptr<Chunk> getChunk(int x, int z);
        VectorXZ normalizeChunkCoordination(int x, int z);
    };
}

#endif /* ChunkManager_hpp */
