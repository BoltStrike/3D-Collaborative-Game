# This example assumes we have a mesh object selected

import bpy
import bmesh
import os
import struct
import math
from mathutils import Euler, Matrix

# Get the object to be exported
obj = bpy.context.object

# Get the faces of the object
polygons = obj.data.polygons

# Get the vertices of the object
verts = obj.data.vertices

# Get the uv coordinates of the object
uv_layer = obj.data.uv_layers[0]

# Get the name of the active object
name = obj.name

# Rotate object to account for y axis being the UP axis for OpenGL
obj.rotation_euler = (math.radians(-90), 0.0, 0.0)
bpy.ops.object.transform_apply( location = False, rotation = True, scale = False )

# Get filepath to this Blender file and find the file to write to
blend_file_path = bpy.data.filepath
directory = os.path.dirname(blend_file_path)
target_file = os.path.join(directory, "{0}.mesh".format(name))

# Create and open file for writing
f = open(target_file, "w")

# Write out length of the name and the name of the object
f.write("{0}{1}".format(len(name), name))
#f.write(bytearray(len(verts)))
#f.write(bytearray(name, 'utf-8'))

# Write the number of vertices
f.write("{0} ".format(len(verts)))
#f.write(bytearray(len(verts)))

# Write all positions of the vertices
for v in verts:
    f.write("{:f} {:f} {:f} ".format(v.co.x, v.co.y, v.co.z))
    #f.write(struct.pack('f'*3,*[v.co.x, v.co.y, v.co.z]))

# Write all normals of the vertices
for v in verts:
    f.write("{:f} {:f} {:f} ".format(
                                    v.normal.x, 
                                    v.normal.y, 
                                    v.normal.z))
    #f.write(struct.pack('f'*3,*[v.normal.x, v.normal.y, v.normal.z]))
                                    
# Write out number of UV coordinates
f.write("{0} ".format(len(uv_layer.data)))
#f.write(bytearray(len(uv_layer.data)))

# Write out all UV coordinates
for u in uv_layer.data:
    f.write("{:f} {:f} ".format(u.uv[0], u.uv[1]))
    #f.write(struct.pack('f'*2,*[u.uv[0], u.uv[1]]))
    
# Write number of faces
f.write("{0} ".format(len(polygons)))
#f.write(bytearray(len(polygons)))

# Write the indicies of each vertex position
# The normals have the same indicies
# The UV coordinates are in order and do not need indices
for p in polygons:
    for i in p.vertices:
        f.write("{0} ".format(i))
        #f.write(bytearray(i))
    
# Close file, we are done writing
f.close()

# Rotate object back to original stance
obj.rotation_euler = (math.radians(90), 0.0, 0.0)
bpy.ops.object.transform_apply( location = False, rotation = True, scale = False )

