// gsmconv

#include <iostream>

#include "gsm.h"
#include "eobj.h"
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cout << "gsmconv - Convert obj models to Battle Mages static model format (.gsm) by ermaccer\n"
			<< "Usage: gsmconv <input> <texture_name>\n";
		return 1;
	}
	eObj Model;
	if (Model.LoadFile(argv[1]))
	{
		gsmHeader gsm;
		sprintf(gsm.strHeader, "ecbnt,t");
		gsm.modelType = MODEL_TYPE_STATIC;
		gsm.version = 1;
		gsm.modelInfo.sectionIdentifier = MODEL_INFO_IDENT;
		gsm.modelInfo.sectionOffset = sizeof(gsmHeader);
		gsm.modelInfo.sectionSize = sizeof(modelInfo);

		gsm.vertices.sectionIdentifier = VERTICES_IDENT;
		gsm.vertices.sectionSize = Model.CalcVertSize();
		gsm.vertices.sectionOffset = sizeof(gsmHeader) + sizeof(modelInfo);
		
		gsm.faces.sectionIdentifier = FACES_IDENT;
		gsm.faces.sectionSize = Model.CalcFaceSize();
		gsm.faces.sectionOffset = sizeof(gsmHeader) + sizeof(modelInfo) + Model.CalcVertSize();

		gsm.endInfo.sectionIdentifier = END_INFO_IDENT;
		gsm.endInfo.sectionOffset = sizeof(gsmHeader) + sizeof(modelInfo) + Model.CalcVertSize() + Model.CalcFaceSize();
		gsm.endInfo.sectionSize = sizeof(endInfo);

		gsm.valueOffset = sizeof(gsmHeader) + sizeof(modelInfo) + Model.CalcVertSize() + Model.CalcFaceSize() + sizeof(endInfo);
		gsm.valueSize = sizeof(int);
		gsm.value_pad = 0;

		modelInfo mi;

		mi.unk = 1;
		mi.type = 1;
		mi.header = 'MSSG';
		mi.faces = Model.GetFaces().size();
		mi.vertices = Model.GetVertexes().v.size();
		sprintf(mi.textName, "%s",argv[2]);

		std::string output = argv[1];
		output += ".gsm";

		std::ofstream oFile(output, std::ofstream::binary);
		oFile.write((char*)&gsm, sizeof(gsmHeader));
		oFile.write((char*)&mi, sizeof(modelInfo));

		for (int i = 0; i < Model.GetVertexes().v.size(); i++)
		{
			oFile.write((char*)&Model.GetVertexes().v[i], sizeof(obj_v));
			oFile.write((char*)&Model.GetVertexes().vn[i], sizeof(obj_vn));
			oFile.write((char*)&Model.GetVertexes().uv[i], sizeof(obj_uv));
		}

		for (int i = 0; i < Model.GetFaces().size(); i++)
		{
			short f[3];
			f[0] = Model.GetFaces()[i].face[0];
			f[1] = Model.GetFaces()[i].face[1];
			f[2] = Model.GetFaces()[i].face[2];
			oFile.write((char*)&f,sizeof(f));
		}


		endInfo ei;
		ei.header = '\0MSG';

		oFile.write((char*)&ei, sizeof(endInfo));
		
		int value = 2;
		oFile.write((char*)&value, sizeof(int));

		std::cout << "Saved to " << output.c_str() << "!" << std::endl;
	}

}
