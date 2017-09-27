#pragma once
#include <type_traits>

#include<Pdfix.h> 
#include <boost/algorithm/string.hpp>

#include <File.h>

#include "PDFixable.h"
#include "PDFixException.h"
#include "PrintJobException.h"
#include <Poco/File.h>

Pdfix_statics

//Dummyklasse, um SFINAE zu nutzen. Wird nie genutzt. Auch nicht, wenn das Interface nicht implementiert wurde.
template<class T, class Enable = void>
class __declspec (dllexport) PDFixJob
{
   PDFixJob(const std::wstring&, const Domain::LeistungId& leistungId)
   {
      throw PDFixException("Das Interface PDFixable muss implementiert sein!");
   }
};

template<class T>
class  __declspec (dllexport) PDFixJob<T, typename std::enable_if<std::is_base_of<PDFixable, T>::value>::type>
{
   std::wstring _filepath;
   Pdfix* _pdfix;
   PdfDoc* _doc;
   bool _isDocumentOpen = true;
   std::unique_ptr<Domain::LeistungId> _leistungId;


   PDFixJob(const std::wstring& filename) : _filepath(filename)
   {
      Pdfix_init("pdfix.dll");
      _pdfix = GetPdfix();

      if (_pdfix)
      {
         bool authorized = _pdfix->Authorize(L"BrAV-Entwicklung@brunata-huerth.de", L"26dnCQtsLxpHn9TV");
         if (authorized)
         {
            wchar_t* filenameArrayPointer = const_cast<wchar_t*>(_filepath.c_str());
            _doc = _pdfix->OpenDoc(filenameArrayPointer, L"");

            if (!_doc)
            {
               throw PDFixException(L"Fehler beim Öffnen des Dokuments: " + _filepath);
            }
         }
         else
         {
            throw PDFixException("Autorisierung bei PDFix nicht möglich.");
         }
      }
      else
      {
         throw PDFixException("Zugriff auf PDFix nicht möglich.");
      }
   }

public:

   PDFixJob(const std::wstring& filename, const Domain::LeistungId& leistungId)
      :PDFixJob(filename)
   {
      _leistungId = std::make_unique<Domain::LeistungId>(leistungId);
   }

   ~PDFixJob()
   {
      if (_doc && _isDocumentOpen)
      {
         _doc->Close();
      }

      if (_pdfix)
      {
         _pdfix->Destroy();
      }
   }

   /**
    * \brief Führt den Druckjob mit der übergebenen Routine aus
    * \return Der Pfad, in dem das Ausgefüllte PDF liegt
    */
   std::string runJob()
   {
      if(std::is_default_constructible<T>::value)
      {
         std::unique_ptr<PDFixable> interfaceObject(new T);
         try
         {
            interfaceObject->setLeistungId(move(_leistungId));
            interfaceObject->fillFields(_doc);
         }catch(PrintJobException& e)
         {
            throw PrintJobException("Es konnte nicht alle Felder befüllt werden.", e);
         }
      }else
      {
         throw PrintJobException("Es wird ein Standardkonstruktor benötigt.");
      }

      std::vector<std::wstring> partsOfFilepath;
      split(partsOfFilepath, _filepath, boost::is_any_of(L"\\"));

      std::wstring filename = partsOfFilepath.at(partsOfFilepath.size() - 1);
      std::string tempPath = GetPathName(BRAV_PATH_TEMP, "");
      std::wstring completeTmpPath = std::wstring(tempPath.begin(), tempPath.end()) + L"\\" + filename;

      Poco::File fileToDelete(std::string(completeTmpPath.begin(), completeTmpPath.end()));
      if (fileToDelete.exists())
      {
         fileToDelete.remove();
      }

      _doc->Save(completeTmpPath.c_str(), kSaveIncremental);
      _doc->Close();
      _isDocumentOpen = false;

      return std::string(completeTmpPath.begin(), completeTmpPath.end());
   }
};
