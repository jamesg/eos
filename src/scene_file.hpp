#ifndef EOS_SCENE_FILE_HPP
#define EOS_SCENE_FILE_HPP

#include <memory>

#include "styx/object.hpp"

#include "scene.hpp"

namespace eos
{
    class lamp;
    class primitive;

    class scene_file : public styx::object
    {
    public:
        static scene_file from_file(const std::string& filename);

        scene get_scene() const;

    private:
        static void load_common(const styx::object&, void*);
        static std::unique_ptr<lamp> load_lamp(const styx::element&);
        static std::unique_ptr<primitive> load_primitive(const styx::element&);

        const styx::list& primitives() const;
        const styx::list& lamps() const;

        scene_file(const styx::element&);
    };
}

#endif

