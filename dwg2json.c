#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <dwg.h>

unsigned output_LINE(Dwg_Object* obj) {
  Dwg_Entity_LINE* line;
  line = obj->tio.entity->tio.LINE;
  printf("    {\n"
         "      \"type\": \"line\",\n"
         "      \"startX\": %f,\n"
         "      \"startY\": %f,\n"
         "      \"startZ\": %f,\n"
         "      \"endX\": %f,\n"
         "      \"endY\": %f,\n"
         "      \"endZ\": %f\n"
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
         "      \"centerX\": %f,\n"
         "      \"centerY\": %f,\n"
         "      \"centerZ\": %f,\n"
         "      \"radius\": %f\n"
         "    }",
         circle->center.x, circle->center.y, circle->center.z, circle->radius);
  return 1;
}

unsigned int output_ARC(Dwg_Object* obj) {
  Dwg_Entity_ARC* arc;
  arc = obj->tio.entity->tio.ARC;
  printf("    {\n"
         "      \"type\": \"circle\",\n"
         "      \"centerX\": %f,\n"
         "      \"centerY\": %f,\n"
         "      \"centerZ\": %f,\n"
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
         "      \"centerX\": %f,\n"
         "      \"centerY\": %f,\n"
         "      \"centerZ\": %f,\n"
         "      \"smallAxisX\": %f,\n"
         "      \"smallAxisY\": %f,\n"
         "      \"smallAxisZ\": %f,\n"
         "      \"extrusionX\": %f,\n"
         "      \"extrusionY\": %f,\n"
         "      \"extrusionZ\": %f,\n"
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

void output_comma(unsigned int count) {
  if (count) {
    printf(",\n");
  }
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
