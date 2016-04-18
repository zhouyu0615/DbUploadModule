#include "stdafx.h"
#include "XmlTransform.h"
#include "TinyXML/tinyxml.h"
#include "TinyXML/tinystr.h"

#include "Util.h"

CXmlTransform::CXmlTransform()
{
	m_pData = CDataProvider::getInstance();
}


CXmlTransform::~CXmlTransform()
{
}


int CXmlTransform::CreateXmlUpdateFile()
{
	TiXmlDocument xmldoc("../Cache/Update.xml");
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "gb2312", "no");
	
	CString cstr("File created at ");
	cstr+= CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
	
	TiXmlComment* comment = new TiXmlComment();
	comment->SetValue(MyCStringToStr(cstr));

	xmldoc.LinkEndChild(decl);
	xmldoc.LinkEndChild(comment);

	TiXmlElement* root= new TiXmlElement("root");
	xmldoc.LinkEndChild(root);

	for (int i = 0; i < m_pData->m_vDbUpdateLog.size();i++)
	{
		if (m_pData->m_vDbUpdateLog[i].m_strUdTbName=="tbProcessPara")
		{    
			TiXmlElement * OperEventNode = new TiXmlElement("OperEventNode");
			int id = m_pData->m_vDbUpdateLog[i].m_lUdId;
			TiXmlElement* infoNode=NULL;
			if (m_pData->m_vDbUpdateLog[i].m_strUdOperType == "Insert"
				|| m_pData->m_vDbUpdateLog[i].m_strUdOperType == "Update")
			{								
				 infoNode = m_pData->m_MpProcessPara[id].GetParaInfoXmlNode();
				
			}
			else if (m_pData->m_vDbUpdateLog[i].m_strUdOperType=="Delete")
			{
				
			}
			OperEventNode->LinkEndChild(infoNode);

			root->LinkEndChild(OperEventNode);
		}
	}


	xmldoc.SaveFile();
	return 0;
}




void CXmlTransform::xmlTest()
{
	const char* demoStart =
		"<?xml version=\"1.0\"  standalone='no' >\n"
		"<!-- Our to do list data -->"
		"<ToDo>\n"
		"<!-- Do I need a secure PDA? -->\n"
		"<Item priority=\"1\" distance='close'> Go to the <bold>Toy store!</bold></Item>"
		"<Item priority=\"2\" distance='none'> Do bills   </Item>"
		"<Item priority=\"2\" distance='far &amp; back'> Look for Evil Dinosaurs! </Item>"
		"</ToDo>";


	TiXmlDocument doc("../Cache/demotest.xml");
	doc.Parse(demoStart);

	if (doc.Error())
	{
		TRACE("Error in %s: %s\n", doc.Value(), doc.ErrorDesc());
		exit(1);
	}
	doc.SaveFile();

	


/*

	TiXmlDocument Testdoc;
    
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "utf-8", "no");

	//添加新的节点元素
	TiXmlElement * RootNode = new TiXmlElement("Root");
		
		
	TiXmlElement* element1=new TiXmlElement("OperEventNode");

	element1->SetAttribute("OperType", "Insert");

	TiXmlElement* tbNameEle = new TiXmlElement("tbName");
	tbNameEle->LinkEndChild(new TiXmlText("tbProPara"));
	
	TiXmlElement* idEle = new TiXmlElement("id");
	idEle->LinkEndChild(new TiXmlText("123"));

	element1->LinkEndChild(tbNameEle);
	element1->LinkEndChild(idEle);

	
	TiXmlComment* comment = new TiXmlComment("This is a testdoc");
	

	TiXmlElement *node = new TiXmlElement("OperEventNode");
	node->LinkEndChild(new TiXmlText("UPDATE"));


	RootNode->LinkEndChild(element1);
	RootNode->LinkEndChild(node);


	//把声明和元素添加到文档
	Testdoc.LinkEndChild(decl);
	Testdoc.LinkEndChild(comment);
	Testdoc.LinkEndChild(RootNode);


	
	Testdoc.SaveFile("Testdoc.xml");

*/

	TiXmlDocument testDoc("中文测试.xml");
	TiXmlDeclaration * decl2 = new TiXmlDeclaration("1.0", "gb2312", "no");

	testDoc.LinkEndChild(decl2);
	//添加新的节点元素
	TiXmlElement * Root = new TiXmlElement("Root");
	Root->LinkEndChild(new TiXmlText("元素"));

	testDoc.LinkEndChild(Root);

	testDoc.SaveFile();

	TiXmlDocument readDoc("中文测试.xml");

	bool load=readDoc.LoadFile();
	TiXmlElement* node;

    node = readDoc.FirstChildElement("Root");
	const char* p=node->GetText();

	std::string str(p);

	readDoc.SaveFile();
}