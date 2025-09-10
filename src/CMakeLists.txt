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
        ../include/engine/Engine.h
        engine/EntityManager.cpp
        engine/ComponentManager.cpp
        engine/SystemManager.cpp
        engine/Engine.cpp
        engine/EntityIdPool.cpp

        ../include/game/Components.h
        ../include/game/TextRenderSystem.h
        ../include/game/InputSystem.h
        game/TextRenderSystem.cpp
        game/InputSystem.cpp
)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable(snake ${SOURCE_FILES})

target_include_directories(snake
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include/engine
        ${PROJECT_SOURCE_DIR}/include/game
)