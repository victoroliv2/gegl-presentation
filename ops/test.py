import Gegl

gegl = Gegl.Node()

gegl_load = gegl.new_child("gegl:load", path="gegl.png")
bg_load = gegl.new_child("gegl:load", path="image.png")

invert = gegl.new_child("gegl:invert")
opacity = gegl.new_child("gegl:opacity", value=0.7)
scale = gegl.new_child("gegl:scale", x=2.0, y=2.0)
translate = gegl.new_child("gegl:translate", x=160.0, y=90.0)

over = gegl.new_child("gegl:over")

write = gegl.new_child("gegl:save", path="tmp.png")

bg_load >> over >> write
gegl_load >> invert >> opacity >> scale >> translate >> over["aux"]

write.process()
