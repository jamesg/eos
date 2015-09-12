#include "scene_file.hpp"

#include <stdexcept>

#include "styx/styx.hpp"

#include "attributes.hpp"
#include "coloured.hpp"
#include "material.hpp"
#include "point_lamp.hpp"
#include "primitive.hpp"
#include "scene.hpp"
#include "soft_lamp.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

eos::scene_file eos::scene_file::from_file(const std::string& filename)
{
    return scene_file(styx::parse_json_file(filename));
}

eos::scene eos::scene_file::get_scene() const
{
    scene out;
    out.set_camera_distance(has_key("distance") ? copy_double("distance") : 2000.0);
    out.set_camera_apeture(has_key("apeture") ? copy_double("apeture") : 0.0);
    for(const styx::element& primitive_e : primitives())
        out.add(scene_file::load_primitive(primitive_e));
    for(const styx::element& lamp_e : lamps())
        out.add(scene_file::load_lamp(lamp_e));
    return out;
}

void eos::scene_file::load_common(const styx::object& o, attributes *p)
{
    if(has_centre *h = dynamic_cast<has_centre*>(p))
        h->set_centre(
                {o.copy_double("x"), o.copy_double("y"), o.copy_double("z")}
                );
}

std::unique_ptr<eos::lamp> eos::scene_file::load_lamp(
        const styx::element& e
        )
{
    styx::object o(e);

    std::unique_ptr<lamp> l;
    if(o.copy_string("type") == "point")
        l.reset(new point_lamp);
    if(o.copy_string("type") == "soft")
        l.reset(new soft_lamp);
    load_common(o, l.get());
    l->set_brightness(o.has_key("brightness") ? o.copy_double("brightness") : 1.0);

    if(soft_lamp *s = dynamic_cast<soft_lamp*>(l.get()))
        s->set_softness(o.copy_double("softness"));
    return std::move(l);
}

std::unique_ptr<eos::primitive> eos::scene_file::load_primitive(
        const styx::element& e
        )
{
    styx::object o(e);

    std::unique_ptr<primitive> shape;
    if(o.copy_string("type") == "sphere")
        shape.reset(new sphere);
    if(o.copy_string("type") == "triangle")
        shape.reset(new triangle);

    if(!shape)
        throw std::runtime_error("not a shape");

    load_common(o, shape.get());

    if(triangle *t = dynamic_cast<triangle*>(shape.get()))
    {
        Eigen::Matrix3d points;
        points <<
                o.copy_double("x1"), o.copy_double("x2"), o.copy_double("x3"),
                o.copy_double("y1"), o.copy_double("y2"), o.copy_double("y3"),
                o.copy_double("z1"), o.copy_double("z2"), o.copy_double("z3");
        t->set_points(points);
    }
    if(sphere *s = dynamic_cast<sphere*>(shape.get()))
        s->set_radius(o.has_key("radius") ? o.copy_double("radius") : 100.0);
    if(coloured *c = dynamic_cast<coloured*>(shape.get()))
        c->set_colour(
                eos::colour::rgba(
                    o.has_key("r") ? o.copy_double("r") : 0.5,
                    o.has_key("g") ? o.copy_double("g") : 0.5,
                    o.has_key("b") ? o.copy_double("b") : 0.5,
                    1.0
                    )
                );
    if(material *m = dynamic_cast<material*>(shape.get()))
        m->set_material_attributes(
                o.copy_double("reflectivity"),
                o.copy_double("specvalue"),
                o.copy_double("specpower")
                );

    return std::move(shape);
}

eos::scene_file::scene_file(const styx::element& e) :
    styx::object(e)
{
}

styx::list eos::scene_file::primitives() const
{
    return copy_list("primitives");
}

styx::list eos::scene_file::lamps() const
{
    return copy_list("lamps");
}
