var fs=require("fs");
var Template=require("./template.js");
var ArgParser=require("./ArgParser.js").ArgParser;
var rdashAlpha = /_([a-z])/ig;

var opts= [
   { 
	   full: 'config', 
	   abbr: 'c',
	   defaultValue:"config.json"
   }, 
   { 
	   full: 'template', 
	   abbr: 't',
	   defaultValue:"template.json"
   },   
   { 
	   full: 'sceneDefine', 
	   abbr: 'sd',
	   defaultValue:"../../Classes/Scenes/SceneDefine.h"
   },
   { 
	   full: 'sceneRegisterData', 
	   abbr: 'srd',
	   defaultValue:"../../Classes/Scenes/sceneRegisterData.h"
   }
];

var result=ArgParser.parse(opts);
// console.log(result);

var configFilePath=result.options.config||"config.json";
var templateFilePath=result.options.template||"template.json";

var sceneDefineFile=result.options.sceneDefine||"../../Classes/Scenes/SceneDefine.h";
var sceneRegisterDataFile=result.options.sceneRegisterData||"../../Classes/Scenes/sceneRegisterData.h";

var templateData=loadTemplate(templateFilePath);
// console.log(templateData)

var configData=loadConfigFile(configFilePath);

var outResult=parseConfigData(configData,templateData);

saveRegisterData(outResult,templateData);

function loadTemplate(filePath){
	var templateContent=fs.readFileSync(filePath);
	var data=JSON.parse(templateContent);
	
	data=data.template;
	var templateData={};
	var item;
	for(var k in data){
		item=data[k];
		if (typeof item=="object") {
			if (item.file) {
				templateData[k]=fs.readFileSync(item.file).toString();
			}else if(item.content){
				templateData[k]=item.content;
			}
		}else{
			templateData[k]=item;
		}
	}
	return templateData;
}


function loadConfigFile(filePath){
	var configContent=fs.readFileSync(filePath);
	return JSON.parse(configContent);
}

function parseConfigData(configData,templateData){
	var defineOut="";
	var unusedOut="";
	var registerIncludeOut="";
	var registerDataOut="";
	
	var scenes=configData.scenes;
	var sceneItem;
	var includePath="";
	
	for (var i in scenes) {
		sceneItem=scenes[i];
		sceneItem=parseConfigSceneItem(sceneItem);
		defineOut+=createDefineData(sceneItem,templateData.sceneDefineItem);
		unusedOut+=createUnusedData(sceneItem,templateData.unusedItem);
		
		
		includePath=createRegisterInclude(sceneItem,templateData.sceneRegisterIncludeItem);
		//check unic include path
		if (registerIncludeOut.indexOf(includePath)==-1) {
			registerIncludeOut+=createRegisterInclude(sceneItem,templateData.sceneRegisterIncludeItem);
		}
		registerDataOut+=createRegisterData(sceneItem,templateData.sceneRegisterDataItem);
	}
	unusedOut=unusedOut.substring(0,unusedOut.length-1);
	return {
		defineData:defineOut,
		unusedData:unusedOut,
		registerInclude:registerIncludeOut,
		registerData:registerDataOut
	};
}

function parseConfigSceneItem(item){
	
	var objItem={};
	
	switch (typeof item) {
		case "string":
			var ucItem=ucfirst(item);
			objItem.name=item;
			objItem.value=item;
			objItem.key="k"+ucItem;
			objItem.creator=ucItem+"::create";
			objItem.path="Scenes/"+ucItem+".h";
			break;
		case "object":
			var ucItem=ucfirst(item.name);
			objItem.name=item.name;
			objItem.value=item.value?item.value:item.name;
			objItem.key=item.key?item.key:("k"+ucItem);
			objItem.creator=item.creator?item.creator:(ucItem+"::create");
			objItem.path=item.path?item.path:("Scenes/"+ucItem);
			break;
		default:
		
	}
	
	return objItem;
}

function createDefineData(sceneItem,tpx){
	return Template.parse(tpx,sceneItem);
}

function createUnusedData(sceneItem,tpx){
	return Template.parse(tpx,sceneItem);
}

function createRegisterInclude(sceneItem,tpx){
	return Template.parse(tpx,sceneItem);
}

function createRegisterData(sceneItem,tpx){
	return Template.parse(tpx,sceneItem);
}


function saveRegisterData(registerData,templateData){
	
	var sceneDefineContent=Template.parse(templateData.sceneDefine,registerData);
	var registerContent=Template.parse(templateData.sceneRegisterData,registerData);
	
	fs.writeFileSync(sceneDefineFile,sceneDefineContent);
	fs.writeFileSync(sceneRegisterDataFile,registerContent);
}

function fcamelCase( all, letter ) {
    return letter.toUpperCase();
}

function camelCase( string ) {
    return string.replace( rdashAlpha, fcamelCase );
}

function ucfirst (str) {
    str += '';
    var f = str.charAt(0).toUpperCase();
    return f + str.substr(1);
}

function lcfirst (str) {
    str += '';
    var f = str.charAt(0).toLowerCase();
    return f + str.substr(1);
}
