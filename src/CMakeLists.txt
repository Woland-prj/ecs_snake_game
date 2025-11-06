set(SOURCE_FILES
        main.cpp
        ../include/engine/core/Signature.h
        ../include/engine/entity/EntityIdPool.h
        ../include/engine/entity/EntityManager.h
        ../include/engine/component/ComponentManager.h
        ../include/engine/component/ComponentPool.h
        ../include/engine/component/IComponentPool.h
        ../include/engine/component/PoolIdNotFoundError.h
        ../include/engine/component/PoolOverflowError.h
        ../include/engine/component/PoolAlreadyExistsError.h
        ../include/engine/system/ISystem.h
        ../include/engine/system/System.h
        ../include/engine/system/SystemManager.h
        ../include/engine/core/SparseSet.h
        ../include/engine/core/EventBus.h
        ../include/engine/Engine.h
        engine/EntityManager.cpp
        engine/ComponentManager.cpp
        engine/SystemManager.cpp
        engine/Engine.cpp
        engine/EntityIdPool.cpp
        ../include/game/Components.h
        ../include/game/TextRenderSystem.h
        ../include/game/TextInputSystem.h
        ../include/game/MovementSystem.h
        ../include/game/InitSystem.h
        ../include/game/CollisionSystem.h
        ../include/game/Events.h
        ../include/game/FoodSpawnSystem.h
        ../include/game/GrowingSystem.h
        ../include/game/GraphicsRenderSystem.h
        ../include/game/GraphicsInputSystem.h
        game/TextRenderSystem.cpp
        game/TextInputSystem.cpp
        game/MovementSystem.cpp
        game/CollisionSystem.cpp
        game/FoodSpawnSystem.cpp
        game/GrowingSystem.cpp
        game/InitSystem.cpp
        game/GraphicsRenderSystem.cpp
        game/GraphicsInputSystem.cpp
)

#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)

find_package(
        SFML
        COMPONENTS Graphics Window System
        REQUIRED)

add_executable(snake ${SOURCE_FILES})

target_link_libraries(snake PRIVATE SFML::Graphics SFML::Window SFML::System)

target_include_directories(snake PRIVATE ${PROJECT_SOURCE_DIR}/include/engine
        ${PROJECT_SOURCE_DIR}/include/game)
