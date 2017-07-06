#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <dwg.h>
#include "suffix.c"

int dwg2json(char *filename);

void output_JSON(Dwg_Data* dwg);

int main(int argc, char *argv[]) {
  REQUIRE_INPUT_FILE_ARG (argc);
  return dwg2json (argv[1]);
}

int dwg2json(char *filename) {
  int error;
  Dwg_Data dwg;

  error = dwg_read_file(filename, &dwg);

  if (!error)
    {
      output_JSON(&dwg);
    }

  dwg_free(&dwg);
  /* This value is the return value for `main',
     so clamp it to either 0 or 1.  */
  return error ? 1 : 0;
}

unsigned output_LINE(Dwg_Object* obj) {
  Dwg_Entity_LINE* line;
  line = obj->tio.entity->tio.LINE;
  printf("    {\n"
         "      \"type\": \"line\",\n"
         "      \"startX\": %f,\n"
         "      \"startY\": %f,\n"
         "      \"endX\": %f,\n"
         "      \"endY\": %f\n"
         "    }",
         line->start.x, line->start.y, line->end.x, line->end.y);
  return 1;
}

unsigned int output_CIRCLE(Dwg_Object* obj) {
  Dwg_Entity_CIRCLE* circle;
  circle = obj->tio.entity->tio.CIRCLE;
  printf("    {\n"
         "      \"type\": \"circle\",\n"
         "      \"centerX\": %f,\n"
         "      \"centerY\": %f,\n"
         "      \"radius\": %f\n"
         "    }",
         circle->center.x, circle->center.y, circle->radius);
  return 1;
}

unsigned int output_ARC(Dwg_Object* obj) {
  Dwg_Entity_ARC* arc;
  arc = obj->tio.entity->tio.ARC;
  printf("    {\n"
         "      \"type\": \"circle\",\n"
         "      \"centerX\": %f,\n"
         "      \"centerY\": %f,\n"
         "      \"startAngle\": %f,\n"
         "      \"endAngle\": %f,\n"
         "      \"radius\": %f\n"
         "    }",
         arc->center.x, arc->center.y, arc->start_angle, arc->end_angle, arc->radius);
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
