#include "c3ds_mesh_loader.h"

C3DSMeshLoader::C3DSMeshLoader(const char* _file, Mesh* _mesh)
{
	strcpy(file, _file);
	mesh = _mesh;
}

C3DSMeshLoader::~C3DSMeshLoader()
{
}

long filelength(int f)
{
	struct stat buf;

	fstat(f, &buf);

	return(buf.st_size);
}

int C3DSMeshLoader::load()
{
	//int i; //Index variable

	FILE *l_file; //File pointer

	unsigned short l_chunk_id = 0; //Chunk identifier
	unsigned int l_chunk_lenght = 0; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	int ret = 0;

	printf("File Name: %s\n", file);
	if ((l_file=fopen (file, "rb"))== NULL)
	{
		printf("Error while opening!!\n");
		return 0; //Open the file
	}

	while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file
		//while(!EOF)
	{
		//getch(); //Insert this command for debug (to wait for keypress for each chuck reading)

		ret = fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
		printf("ChunkID: %x\n",l_chunk_id); 
		ret = fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id)
		{
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d 
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4d4d: 
				break;    

				//----------------- EDIT3DS -----------------
				// Description: 3D Editor chunk, objects layout info 
				// Chunk ID: 3d3d (hex)
				// Chunk Lenght: 0 + sub chunks
				//-------------------------------------------
			case 0x3d3d:
				break;

				//--------------- EDIT_OBJECT ---------------
				// Description: Object block, info for each object
				// Chunk ID: 4000 (hex)
				// Chunk Lenght: len(object name) + sub chunks
				//-------------------------------------------
			case 0x4000: 
				{
					int i=0;
					do
					{
						ret = fread (&l_char, 1, 1, l_file);
						mesh->name[i]=l_char;
						i++;
					}while(l_char != '\0' && i<20);
				}

				break;

				//--------------- OBJ_TRIMESH ---------------
				// Description: Triangular mesh, contains chunks for 3d mesh info
				// Chunk ID: 4100 (hex)
				// Chunk Lenght: 0 + sub chunks
				//-------------------------------------------
			case 0x4100:
				break;

				//--------------- TRI_VERTEXL ---------------
				// Description: Vertices list
				// Chunk ID: 4110 (hex)
				// Chunk Lenght: 1 x unsigned short (number of vertices) 
				//             + 3 x float (vertex coordinates) x (number of vertices)
				//             + sub chunks
				//-------------------------------------------
			case 0x4110: 
				{
					ret = fread (&l_qty, sizeof (unsigned short), 1, l_file);
					//p_object->vertices_qty = l_qty;
					//mesh->vertices.resize(l_qty);
					printf("Number of vertices: %d\n",l_qty);
					Vertex cur_vertex;
					for (int i=0; i<l_qty; i++)
					{

						ret = fread (&cur_vertex.x, sizeof(float), 1, l_file);
						printf("Vertices list x: %f\n", cur_vertex.x);
						ret = fread (&cur_vertex.y, sizeof(float), 1, l_file);
						printf("Vertices list y: %f\n", cur_vertex.y);
						ret = fread (&cur_vertex.z, sizeof(float), 1, l_file);
						printf("Vertices list z: %f\n", cur_vertex.z);

						//printf("Before!\n");
						mesh->vertices.push_back(cur_vertex);
						//printf("After!\n");
					}
				}
				break;

				//--------------- TRI_FACEL1 ----------------
				// Description: Polygons (faces) list
				// Chunk ID: 4120 (hex)
				// Chunk Lenght: 1 x unsigned short (number of polygons) 
				//             + 3 x unsigned short (polygon points) x (number of polygons)
				//             + sub chunks
				//-------------------------------------------
			case 0x4120:
				{
					ret = fread (&l_qty, sizeof (unsigned short), 1, l_file);
					//p_object->polygons_qty = l_qty;
					mesh->faces.resize(l_qty);
					printf("Number of polygons: %d\n",l_qty); 
					Face cur_face;
					for (int i=0; i<l_qty; i++)
					{
						ret = fread (&cur_face.indices[0].vid, sizeof (unsigned short), 1, l_file);
						printf("Polygon point a: %d\n", cur_face.indices[0].vid);
						ret = fread (&cur_face.indices[1].vid, sizeof (unsigned short), 1, l_file);
						printf("Polygon point b: %d\n", cur_face.indices[1].vid);
						ret = fread (&cur_face.indices[2].vid, sizeof (unsigned short), 1, l_file);
						printf("Polygon point c: %d\n", cur_face.indices[2].vid);
						ret = fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
						printf("Face flags: %x\n",l_face_flags);

						// filling the texcoord and normal
						for(int j = 0 ; j < 3 ; j ++)
						{
							// texcoord index = vertex index
							cur_face.indices[j].tid = cur_face.indices[j].vid;
						}	   

						mesh->faces[i] = cur_face;
					}

					printf("Face count: %d\n", mesh->faces.size());
				}
				break;

				//------------- TRI_MAPPINGCOORS ------------
				// Description: Vertices list
				// Chunk ID: 4140 (hex)
				// Chunk Lenght: 1 x unsigned short (number of mapping points) 
				//             + 2 x float (mapping coordinates) x (number of mapping points)
				//             + sub chunks
				//-------------------------------------------
			case 0x4140:
				{
					ret = fread (&l_qty, sizeof (unsigned short), 1, l_file);
					mesh->texcoords.resize(l_qty);
					for (int i=0; i<l_qty; i++)
					{
						TexCoord cur_coord;

						ret = fread (&cur_coord.x, sizeof (float), 1, l_file);
						printf("Mapping list u: %f\n",cur_coord.x);
						ret = fread (&cur_coord.y, sizeof (float), 1, l_file);
						printf("Mapping list v: %f\n",cur_coord.y);

						mesh->texcoords[i] = cur_coord;
					}
				}
				break;

				//----------- Skip unknow chunks ------------
				//We need to skip all the chunks that currently we don't use
				//We use the chunk lenght information to set the file pointer
				//to the same level next chunk
				//-------------------------------------------
			default:
				fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
		} 
	}
	fclose (l_file); // Closes the file stream

	return 1;
}
