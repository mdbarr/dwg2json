#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <dwg.h>

void output_comma(unsigned int count) {
  if (count) {
    printf(",\n");
  }
}

unsigned output_LINE(Dwg_Object* obj) {
  Dwg_Entity_LINE* line;
  line = obj->tio.entity->tio.LINE;
  printf("    {\n"
         "      \"type\": \"line\",\n"
         "      \"start\": {\n"
         "        \"x\": %f,\n"
         "        \"y\": %f,\n"
         "        \"z\": %f\n"
         "      },\n"
         "      \"end\": {\n"
         "        \"x\": %f,\n"
         "        \"y\": %f,\n"
         "        \"z\": %f\n"
         "      }\n"
         "    }",
         line->start.x, line->start.y, line->start.z,
         line->end.x, line->end.y, line->start.z);
  return 1;
}

unsigned int output_CIRCLE(Dwg_Object* obj) {
  Dwg_Entity_CIRCLE* circle;
  circle = obj->tio.entity->tio.CIRCLE;
  printf("    {\n"
         "      \"type\": \"circle\",\n"
         "      \"center\": {\n"
         "        \"x\": %f,\n"
         "        \"y\": %f,\n"
         "        \"z\": %f\n"
         "      },\n"
         "      \"radius\": %f\n"
         "    }",
         circle->center.x, circle->center.y, circle->center.z, circle->radius);
  return 1;
}

unsigned int output_ARC(Dwg_Object* obj) {
  Dwg_Entity_ARC* arc;
  arc = obj->tio.entity->tio.ARC;
  printf("    {\n"
         "      \"type\": \"arc\",\n"
         "      \"center\": {\n"
         "        \"x\": %f,\n"
         "        \"y\": %f,\n"
         "        \"z\": %f\n"
         "      },\n"
         "      \"startAngle\": %f,\n"
         "      \"endAngle\": %f,\n"
         "      \"radius\": %f\n"
         "    }",
         arc->center.x, arc->center.y, arc->center.z, arc->start_angle, arc->end_angle, arc->radius);
  return 1;
}

unsigned int output_ELLIPSE(Dwg_Object* obj) {
  Dwg_Entity_ELLIPSE* ellipse;
  ellipse = obj->tio.entity->tio.ELLIPSE;
  printf("    {\n"
         "      \"type\": \"ellipse\",\n"
         "      \"center\": {\n"
         "        \"x\": %f,\n"
         "        \"y\": %f,\n"
         "        \"z\": %f\n"
         "      },\n"
         "      \"smallAxis\": {\n"
         "        \"x\": %f,\n"
         "        \"y\": %f,\n"
         "        \"z\": %f\n"
         "      },\n"
         "      \"extrusion\": {\n"
         "        \"x\": %f,\n"
         "        \"y\": %f,\n"
         "        \"z\": %f\n"
         "      },\n"
         "      \"axisRatio\": %f,\n"
         "      \"startAngle\": %f,\n"
         "      \"endAngle\": %f\n"
         "    }",
         ellipse->center.x, ellipse->center.y, ellipse->center.z,
         ellipse->sm_axis.x, ellipse->sm_axis.y, ellipse->sm_axis.z,
         ellipse->extrusion.x, ellipse->extrusion.y, ellipse->extrusion.z,
         ellipse->axis_ratio, ellipse->start_angle, ellipse->end_angle);
  return 1;
}

unsigned int output_SPLINE(Dwg_Object* obj) {
  Dwg_Entity_SPLINE* spline;
  unsigned int i;
  spline = obj->tio.entity->tio.SPLINE;
  printf("    {\n"
         "      \"type\": \"spline\",\n"
         "      \"scenario\": %u,\n"
         "      \"degree\": %u,\n"
         "      \"fitTolerancee\": %f,\n"
         "      \"beginTangentVector\": {\n"
         "         \"x\": %f,\n"
         "         \"y\": %f,\n"
         "         \"z\": %f\n"
         "      },\n"
         "      \"endTangentVector\": {\n"
         "         \"x\": %f,\n"
         "         \"y\": %f,\n"
         "         \"z\": %f\n"
         "      },\n"
         "      \"rational\": %u,\n"
         "      \"closed\": %u,\n"
         "      \"periodic\": %u,\n"
         "      \"weighted\": %u,\n"
         "      \"knotTolerancee\": %f,\n"
         "      \"controlPointTolerancee\": %f,\n",
         spline->scenario, spline->degree, spline->fit_tol,
         spline->beg_tan_vec.x, spline->beg_tan_vec.y, spline->beg_tan_vec.z,
         spline->end_tan_vec.x, spline->end_tan_vec.y, spline->end_tan_vec.z,
         spline->rational, spline->closed_b, spline->periodic, spline->weighted,
         spline->knot_tol, spline->ctrl_tol);

  printf("      \"fitPoints\": [\n");
  for (i = 0; i < spline->num_fit_pts; i++) {
      printf("        {\n"
             "          \"x\": %f,\n"
             "          \"y\": %f,\n"
             "          \"z\": %f\n"
             "        }",
             spline->fit_pts[i].x, spline->fit_pts[i].y, spline->fit_pts[i].z);
    if (i < spline->num_fit_pts - 1) {
      printf(",");
    }
    printf("\n");
  }

  printf("\n"
         "      ],\n");

  printf("      \"knots\": [\n");
  for (i = 0; i < spline->num_knots; i++) {
    printf("        %f", spline->knots[i]);
    if (i < spline->num_knots - 1) {
      printf(",");
    }
    printf("\n");
  }

  printf("\n"
         "      ],\n");

  printf("      \"controlPoints\": [\n");
  for (i = 0; i < spline->num_ctrl_pts; i++) {
      printf("        {\n"
             "          \"x\": %f,\n"
             "          \"y\": %f,\n"
             "          \"z\": %f,\n"
             "          \"w\": %f\n"
             "        }",
             spline->ctrl_pts[i].x, spline->ctrl_pts[i].y,
             spline->ctrl_pts[i].z, spline->ctrl_pts[i].w);
    if (i < spline->num_ctrl_pts - 1) {
      printf(",");
    }
    printf("\n");
  }

  printf("\n"
         "      ]\n"
         "    }");

  return 1;
}

void ouput_VERTEX_2D(Dwg_Entity_VERTEX_2D* vertex) {
  printf("        {\n"
         "          \"x\": %f,\n"
         "          \"y\": %f\n"
         "        }",
         vertex->point.x, vertex->point.y);
}

unsigned int output_POLYLINE_2D(Dwg_Object* obj) {
  Dwg_Entity_POLYLINE_2D* poly2d;
  Dwg_Entity_VERTEX_2D* vertex;
  Dwg_Object * vertexObj;
  unsigned int count = 0;

  poly2d = obj->tio.entity->tio.POLYLINE_2D;
  printf("    {\n"
         "      \"type\": \"polyline2d\",\n"
         "      \"flags\": %u,\n"
         "      \"curveType\": %u,\n"
         "      \"startWidth\": %f,\n"
         "      \"endWidth\": %f,\n"
         "      \"thickness\": %f,\n"
         "      \"elevation\": %f,\n"
         "      \"extrusion\": {\n"
         "         \"x\": %f,\n"
         "         \"y\": %f,\n"
         "         \"z\": %f\n"
         "      },\n"
         "      \"vertices\": [\n",
         poly2d->flags, poly2d->curve_type,
         poly2d->start_width, poly2d->end_width,
         poly2d->thickness, poly2d->elevation,
         poly2d->extrusion.x, poly2d->extrusion.y, poly2d->extrusion.z);


  vertexObj = poly2d->first_vertex->obj;
  while(vertexObj != poly2d->last_vertex->obj) {
    vertex = vertexObj->tio.entity->tio.VERTEX_2D;
    ouput_VERTEX_2D(vertex);

    count++;
    output_comma(count);

    vertexObj = dwg_next_object(vertexObj);
  }
  vertex = vertexObj->tio.entity->tio.VERTEX_2D;
  ouput_VERTEX_2D(vertex);

  printf("\n"
         "      ]\n"
         "    }");

  return 1;
}

void ouput_VERTEX_3D(Dwg_Entity_VERTEX_3D* vertex) {
  printf("        {\n"
         "          \"x\": %f,\n"
         "          \"y\": %f,\n"
         "          \"z\": %f\n"
         "        }",
         vertex->point.x, vertex->point.y, vertex->point.z);
}

unsigned int output_POLYLINE_3D(Dwg_Object* obj) {
  Dwg_Entity_POLYLINE_3D* poly3d;
  Dwg_Entity_VERTEX_3D* vertex;
  Dwg_Object * vertexObj;
  unsigned int count = 0;

  poly3d = obj->tio.entity->tio.POLYLINE_3D;
  printf("    {\n"
         "      \"type\": \"polyline3d\",\n"
         "      \"flags1\": %u,\n"
         "      \"flags2\": %u,\n"
         "      \"vertices\": [\n",
         poly3d->flags_1, poly3d->flags_2);

  vertexObj = poly3d->first_vertex->obj;
  while(vertexObj != poly3d->last_vertex->obj) {
    vertex = vertexObj->tio.entity->tio.VERTEX_3D;
    ouput_VERTEX_3D(vertex);

    count++;
    output_comma(count);

    vertexObj = dwg_next_object(vertexObj);
  }
  vertex = vertexObj->tio.entity->tio.VERTEX_3D;
  ouput_VERTEX_3D(vertex);

  printf("\n"
         "      ]\n"
         "    }");
  return 1;
}

unsigned int output_object(Dwg_Object* obj, unsigned int count) {
  if (!obj) {
    fprintf(stderr, "object is NULL\n");
    return 0;
  } else if (obj->type == DWG_TYPE_LINE) {
    output_comma(count);
    return output_LINE(obj);
  } else if (obj->type == DWG_TYPE_CIRCLE) {
    output_comma(count);
    return output_CIRCLE(obj);
  } else if (obj->type == DWG_TYPE_ARC) {
    output_comma(count);
    return output_ARC(obj);
  } else if (obj->type == DWG_TYPE_ELLIPSE) {
    output_comma(count);
    return output_ELLIPSE(obj);
  } else if (obj->type == DWG_TYPE_SPLINE) {
    output_comma(count);
    return output_SPLINE(obj);
  } else if (obj->type == DWG_TYPE_POLYLINE_2D) {
    output_comma(count);
    return output_POLYLINE_2D(obj);
  } else if (obj->type == DWG_TYPE_POLYLINE_3D) {
    output_comma(count);
    return output_POLYLINE_3D(obj);
  }
  return 0;
}

void output_JSON(Dwg_Data* dwg) {
  Dwg_Object *obj;

  unsigned int i;
  unsigned int count = 0;

  printf("{\n"
         "  \"type\": \"dwg\",\n"
         "  \"entities\": [\n");

  for (i = 0; i < dwg->num_objects; i++) {
      obj = &dwg->object[i];
      count += output_object(obj, count);
  }

  printf("\n"
         "  ],\n"
         "  \"count\": %d\n"
         "}\n",
         count);
}

int dwg2json(char *filename) {
  int error;
  Dwg_Data dwg;

  error = dwg_read_file(filename, &dwg);

  if (!error) {
    output_JSON(&dwg);
  }

  dwg_free(&dwg);
  return error ? 1 : 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: dwg2json FILE.dwg\n");
  }
  return dwg2json(argv[1]);
}
