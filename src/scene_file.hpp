#ifndef EOS_SCENE_FILE_HPP
#define EOS_SCENE_FILE_HPP

#include <memory>

#include "styx/object.hpp"

#include "scene.hpp"

namespace eos
{
    class primitive;

    class scene_file : public styx::object
    {
    public:
        static scene_file from_file(const std::string& filename);

        scene get_scene() const;

    private:
        static std::unique_ptr<primitive> load_primitive(const styx::element&);

        const styx::list& primitives() const;

        scene_file(const styx::element&);
    };
}

#endif

