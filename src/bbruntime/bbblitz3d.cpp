#include "std.h"
#include "bbblitz3d.h"

void blitz3d_link(void (*rtSym)(std::string sym))
{
    rtSym("LoaderMatrix$file_ext#xx#xy#xz#yx#yy#yz#zx#zy#zz");
    rtSym("HWMultiTex%enable");
    rtSym("%HWTexUnits");
    rtSym("%GfxDriverCaps3D");
    rtSym("WBuffer%enable");
    rtSym("Dither%enable");
    rtSym("AntiAlias%enable");
    rtSym("WireFrame%enable");
    rtSym("AmbientLight#red#green#blue");
    rtSym("ClearCollisions");
    rtSym("Collisions%source_type%destination_type%method%response");
    rtSym("UpdateWorld#elapsed_time=1");
    rtSym("CaptureWorld");
    rtSym("RenderWorld#tween=1");
    rtSym("ClearWorld%entities=1%brushes=1%textures=1");
    rtSym("%ActiveTextures");
    rtSym("%TrisRendered");
    rtSym("#Stats3D%type");

    rtSym("%CreateTexture%width%height%flags=0%frames=1");
    rtSym("%LoadTexture$file%flags=1");
    rtSym("%LoadAnimTexture$file%flags%width%height%first%count");
    rtSym("FreeTexture%texture");
    rtSym("TextureBlend%texture%blend");
    rtSym("TextureCoords%texture%coords");
    rtSym("ScaleTexture%texture#u_scale#v_scale");
    rtSym("RotateTexture%texture#angle");
    rtSym("PositionTexture%texture#u_offset#v_offset");
    rtSym("%TextureWidth%texture");
    rtSym("%TextureHeight%texture");
    rtSym("$TextureName%texture");
    rtSym("SetCubeFace%texture%face");
    rtSym("SetCubeMode%texture%mode");
    rtSym("%TextureBuffer%texture%frame=0");
    rtSym("ClearTextureFilters");
    rtSym("TextureFilter$match_text%texture_flags=0");

    rtSym("%CreateBrush#red=255#green=255#blue=255");
    rtSym("%LoadBrush$file%texture_flags=1#u_scale=1#v_scale=1");
    rtSym("FreeBrush%brush");
    rtSym("BrushColor%brush#red#green#blue");
    rtSym("BrushAlpha%brush#alpha");
    rtSym("BrushShininess%brush#shininess");
    rtSym("BrushTexture%brush%texture%frame=0%index=0");
    rtSym("%GetBrushTexture%brush%index=0");
    rtSym("BrushBlend%brush%blend");
    rtSym("BrushFX%brush%fx");

    rtSym("%LoadMesh$file%parent=0");
    rtSym("%LoadAnimMesh$file%parent=0");
    rtSym("%LoadAnimSeq%entity$file");

    rtSym("%CreateMesh%parent=0");
    rtSym("%CreateCube%parent=0");
    rtSym("%CreateSphere%segments=8%parent=0");
    rtSym("%CreateCylinder%segments=8%solid=1%parent=0");
    rtSym("%CreateCone%segments=8%solid=1%parent=0");
    rtSym("%CopyMesh%mesh%parent=0");
    rtSym("ScaleMesh%mesh#x_scale#y_scale#z_scale");
    rtSym("RotateMesh%mesh#pitch#yaw#roll");
    rtSym("PositionMesh%mesh#x#y#z");
    rtSym("FitMesh%mesh#x#y#z#width#height#depth%uniform=0");
    rtSym("FlipMesh%mesh");
    rtSym("PaintMesh%mesh%brush");
    rtSym("AddMesh%source_mesh%dest_mesh");
    rtSym("UpdateNormals%mesh");
    rtSym("LightMesh%mesh#red#green#blue#range=0#x=0#y=0#z=0");
    rtSym("#MeshWidth%mesh");
    rtSym("#MeshHeight%mesh");
    rtSym("#MeshDepth%mesh");
    rtSym("%MeshesIntersect%mesh_a%mesh_b");
    rtSym("%CountSurfaces%mesh");
    rtSym("%GetSurface%mesh%surface_index");
    rtSym("MeshCullBox%mesh#x#y#z#width#height#depth");

    rtSym("%CreateSurface%mesh%brush=0");
    rtSym("%GetSurfaceBrush%surface");
    rtSym("%GetEntityBrush%entity");
    rtSym("%FindSurface%mesh%brush");
    rtSym("ClearSurface%surface%clear_vertices=1%clear_triangles=1");
    rtSym("PaintSurface%surface%brush");
    rtSym("%AddVertex%surface#x#y#z#u=0#v=0#w=1");
    rtSym("%AddTriangle%surface%v0%v1%v2");
    rtSym("VertexCoords%surface%index#x#y#z");
    rtSym("VertexNormal%surface%index#nx#ny#nz");
    rtSym("VertexColor%surface%index#red#green#blue#alpha=1");
    rtSym("VertexTexCoords%surface%index#u#v#w=1%coord_set=0");
    rtSym("%CountVertices%surface");
    rtSym("%CountTriangles%surface");
    rtSym("#VertexX%surface%index");
    rtSym("#VertexY%surface%index");
    rtSym("#VertexZ%surface%index");
    rtSym("#VertexNX%surface%index");
    rtSym("#VertexNY%surface%index");
    rtSym("#VertexNZ%surface%index");
    rtSym("#VertexRed%surface%index");
    rtSym("#VertexGreen%surface%index");
    rtSym("#VertexBlue%surface%index");
    rtSym("#VertexAlpha%surface%index");
    rtSym("#VertexU%surface%index%coord_set=0");
    rtSym("#VertexV%surface%index%coord_set=0");
    rtSym("#VertexW%surface%index%coord_set=0");
    rtSym("%TriangleVertex%surface%index%vertex");

    rtSym("%CreateCamera%parent=0");
    rtSym("CameraZoom%camera#zoom");
    rtSym("CameraRange%camera#near#far");
    rtSym("CameraClsColor%camera#red#green#blue");
    rtSym("CameraClsMode%camera%cls_color%cls_zbuffer");
    rtSym("CameraProjMode%camera%mode");
    rtSym("CameraViewport%camera%x%y%width%height");
    rtSym("CameraFogColor%camera#red#green#blue");
    rtSym("CameraFogRange%camera#near#far");
    rtSym("CameraFogMode%camera%mode");
    rtSym("CameraProject%camera#x#y#z");
    rtSym("#ProjectedX");
    rtSym("#ProjectedY");
    rtSym("#ProjectedZ");

    rtSym("%EntityInView%entity%camera");
    rtSym("%EntityVisible%src_entity%dest_entity");

    rtSym("%EntityPick%entity#range");
    rtSym("%LinePick#x#y#z#dx#dy#dz#radius=0");
    rtSym("%CameraPick%camera#viewport_x#viewport_y");

    rtSym("#PickedX");
    rtSym("#PickedY");
    rtSym("#PickedZ");
    rtSym("#PickedNX");
    rtSym("#PickedNY");
    rtSym("#PickedNZ");
    rtSym("#PickedTime");
    rtSym("%PickedEntity");
    rtSym("%PickedSurface");
    rtSym("%PickedTriangle");

    rtSym("%CreateLight%type=1%parent=0");
    rtSym("LightColor%light#red#green#blue");
    rtSym("LightRange%light#range");
    rtSym("LightConeAngles%light#inner_angle#outer_angle");

    rtSym("%CreatePivot%parent=0");

    rtSym("%CreateSprite%parent=0");
    rtSym("%LoadSprite$file%texture_flags=1%parent=0");
    rtSym("RotateSprite%sprite#angle");
    rtSym("ScaleSprite%sprite#x_scale#y_scale");
    rtSym("HandleSprite%sprite#x_handle#y_handle");
    rtSym("SpriteViewMode%sprite%view_mode");

    rtSym("%LoadMD2$file%parent=0");
    rtSym("AnimateMD2%md2%mode=1#speed=1%first_frame=0%last_frame=9999#transition=0");
    rtSym("#MD2AnimTime%md2");
    rtSym("%MD2AnimLength%md2");
    rtSym("%MD2Animating%md2");

    rtSym("%LoadBSP$file#gamma_adj=0%parent=0");
    rtSym("BSPLighting%bsp%use_lightmaps");
    rtSym("BSPAmbientLight%bsp#red#green#blue");

    rtSym("%CreateMirror%parent=0");

    rtSym("%CreatePlane%segments=1%parent=0");

    rtSym("%CreateTerrain%grid_size%parent=0");
    rtSym("%LoadTerrain$heightmap_file%parent=0");
    rtSym("TerrainDetail%terrain%detail_level%morph=0");
    rtSym("TerrainShading%terrain%enable");
    rtSym("#TerrainX%terrain#world_x#world_y#world_z");
    rtSym("#TerrainY%terrain#world_x#world_y#world_z");
    rtSym("#TerrainZ%terrain#world_x#world_y#world_z");
    rtSym("%TerrainSize%terrain");
    rtSym("#TerrainHeight%terrain%terrain_x%terrain_z");
    rtSym("ModifyTerrain%terrain%terrain_x%terrain_z#height%realtime=0");

    rtSym("%CreateListener%parent#rolloff_factor=1#doppler_scale=1#distance_scale=1");
    rtSym("%EmitSound%sound%entity");

    rtSym("%CopyEntity%entity%parent=0");

    rtSym("#EntityX%entity%global=0");
    rtSym("#EntityY%entity%global=0");
    rtSym("#EntityZ%entity%global=0");
    rtSym("#EntityPitch%entity%global=0");
    rtSym("#EntityYaw%entity%global=0");
    rtSym("#EntityRoll%entity%global=0");
    rtSym("#GetMatElement%entity%row%column");
    rtSym("TFormPoint#x#y#z%source_entity%dest_entity");
    rtSym("TFormVector#x#y#z%source_entity%dest_entity");
    rtSym("TFormNormal#x#y#z%source_entity%dest_entity");
    rtSym("#TFormedX");
    rtSym("#TFormedY");
    rtSym("#TFormedZ");
    rtSym("#VectorYaw#x#y#z");
    rtSym("#VectorPitch#x#y#z");
    rtSym("#DeltaPitch%src_entity%dest_entity");
    rtSym("#DeltaYaw%src_entity%dest_entity");

    rtSym("ResetEntity%entity");
    rtSym("EntityType%entity%collision_type%recursive=0");
    rtSym("EntityPickMode%entity%pick_geometry%obscurer=1");
    rtSym("%GetParent%entity");
    rtSym("%GetEntityType%entity");
    rtSym("EntityRadius%entity#x_radius#y_radius=0");
    rtSym("EntityBox%entity#x#y#z#width#height#depth");
    rtSym("#EntityDistance%source_entity%destination_entity");
    rtSym("%EntityCollided%entity%type");

    rtSym("%CountCollisions%entity");
    rtSym("#CollisionX%entity%collision_index");
    rtSym("#CollisionY%entity%collision_index");
    rtSym("#CollisionZ%entity%collision_index");
    rtSym("#CollisionNX%entity%collision_index");
    rtSym("#CollisionNY%entity%collision_index");
    rtSym("#CollisionNZ%entity%collision_index");
    rtSym("#CollisionTime%entity%collision_index");
    rtSym("%CollisionEntity%entity%collision_index");
    rtSym("%CollisionSurface%entity%collision_index");
    rtSym("%CollisionTriangle%entity%collision_index");

    rtSym("MoveEntity%entity#x#y#z");
    rtSym("TurnEntity%entity#pitch#yaw#roll%global=0");
    rtSym("TranslateEntity%entity#x#y#z%global=0");
    rtSym("PositionEntity%entity#x#y#z%global=0");
    rtSym("ScaleEntity%entity#x_scale#y_scale#z_scale%global=0");
    rtSym("RotateEntity%entity#pitch#yaw#roll%global=0");
    rtSym("PointEntity%entity%target#roll=0");
    rtSym("AlignToVector%entity#vector_x#vector_y#vector_z%axis#rate=1");
    rtSym("SetAnimTime%entity#time%anim_seq=0");
    rtSym("Animate%entity%mode=1#speed=1%sequence=0#transition=0");
    rtSym("SetAnimKey%entity%frame%pos_key=1%rot_key=1%scale_key=1");
    rtSym("%AddAnimSeq%entity%length");
    rtSym("%ExtractAnimSeq%entity%first_frame%last_frame%anim_seq=0");
    rtSym("%AnimSeq%entity");
    rtSym("#AnimTime%entity");
    rtSym("%AnimLength%entity");
    rtSym("%Animating%entity");

    rtSym("EntityParent%entity%parent%global=1");
    rtSym("%CountChildren%entity");
    rtSym("%GetChild%entity%index");
    rtSym("%FindChild%entity$name");

    rtSym("PaintEntity%entity%brush");
    rtSym("EntityColor%entity#red#green#blue");
    rtSym("EntityAlpha%entity#alpha");
    rtSym("EntityShininess%entity#shininess");
    rtSym("EntityTexture%entity%texture%frame=0%index=0");
    rtSym("EntityBlend%entity%blend");
    rtSym("EntityFX%entity%fx");
    rtSym("EntityAutoFade%entity#near#far");
    rtSym("EntityOrder%entity%order");
    rtSym("HideEntity%entity");
    rtSym("ShowEntity%entity");
    rtSym("FreeEntity%entity");

    rtSym("NameEntity%entity$name");
    rtSym("$EntityName%entity");
    rtSym("$EntityClass%entity");
}
