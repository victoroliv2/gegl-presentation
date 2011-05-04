#include <gegl.h>
#include <glib/gprintf.h>

gint
main (gint    argc,
      gchar **argv)
{
  g_thread_init (NULL);
  gegl_init (&argc, &argv);  /* initialize the GEGL library */

  {
    /* instantiate a graph */
    GeglNode *gegl = gegl_node_new ();

    /*< The image nodes representing operations we want to perform */
    GeglNode *bg_load = gegl_node_new_child (gegl,
                               "operation", "gegl:load",
                               "path", "image.png",
                               NULL);
                               
    GeglNode *gegl_load = gegl_node_new_child (gegl,
                                "operation", "gegl:load",
                                "path", "gegl.png",
                                NULL);

    GeglNode *invert    = gegl_node_new_child (gegl,
                                "operation", "gegl:invert",
                                NULL);
                                
    GeglNode *opacity  = gegl_node_new_child (gegl,
                                "operation", "gegl:opacity",
                                "value", 0.7,
                                NULL);

    GeglNode *scale   = gegl_node_new_child (gegl,
                                "operation", "gegl:scale",
                                "x", 2.0,
                                "y", 2.0,
                                NULL);

    GeglNode *translate = gegl_node_new_child (gegl,
                                "operation", "gegl:translate",
                                "x", 160.0,
                                "y", 90.0,
                                NULL);
                                
    GeglNode *over     = gegl_node_new_child (gegl,
                                 "operation", "gegl:over",
                                 NULL);
                                
    GeglNode *write     = gegl_node_new_child (gegl,
                                 "operation", "gegl:save",
                                 "path", "output_save.png",
                                 NULL);

    gegl_node_link_many  (gegl_load, invert, opacity, scale, translate, NULL);
    gegl_node_link_many  (bg_load, over, write, NULL);
    gegl_node_connect_to (translate, "output", over, "aux");
    
    gegl_node_process (write);

    /* free resources used by the graph and the nodes it owns */
    g_object_unref (gegl);
  }

  /* free resources globally used by GEGL */
  gegl_exit ();

  return 0;
}
