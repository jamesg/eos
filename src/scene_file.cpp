#include "scene_file.hpp"

#include <stdexcept>

#include "styx/styx.hpp"

#include "coloured.hpp"
#include "material.hpp"
#include "primitive.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

eos::scene_file eos::scene_file::from_file(const std::string& filename)
{
    return scene_file(styx::from_file(filename));
}

eos::scene eos::scene_file::get_scene() const
{
    scene out;
    for(const styx::element& primitive_e : primitives())
        out.add(scene_file::load_primitive(primitive_e));
    return out;
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
    {
        s->set_centre(
                Eigen::Vector3d(
                    o.copy_double("x"),
                    o.copy_double("y"),
                    o.copy_double("z")
                    )
                );
        s->set_radius(o.copy_double("radius"));
    }
    if(coloured *c = dynamic_cast<coloured*>(shape.get()))
        c->set_colour(
                eos::pixel(
                    o.copy_double("r"),
                    o.copy_double("g"),
                    o.copy_double("b")
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

const styx::list& eos::scene_file::primitives() const
{
    return get_list("primitives");
}
