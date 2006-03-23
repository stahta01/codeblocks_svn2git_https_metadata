#ifndef WXSCODER_H
#define WXSCODER_H

#include <cbeditor.h>

/** \brief Class putting new code into proper files
 *
 * \warning Current implementation does not shedule coded upgrades which may 
 *          cause bad results in performance.
 */
class wxsCoder
{
	public:

		/** \brief Function notifying about change of block of code in file
		 *
		 * Code should use tabs for indentation and will be automatically
		 * indented relatively to code header.
		 *
		 * \param FileName Full path for processed file
		 * \param Header Header beginning code block
		 * \param End Sequence ending code block
		 * \param Code new code
		 * \param Immediately flag forcing immediate apply (currently not used 
		 *        but may be aded in future when updates will be sheduled)
		 * \param CodeHasHeader if true, heder will also be recreated 
		 *        (new hwader should be placed at the beginning of Code)
		 * \param CodeHasEnd if true, ending sequence will also be recreated
		 *        (new ending sequence should be placed at the end of Code)
		 */
		void AddCode(
            const wxString& FileName,
            const wxString& Header,
            const wxString& End,
            const wxString& Code,
            bool Immediately=true,
            bool CodeHasHeader=false,
            bool CodeHasEnd=false);

		/** \brief Function reading block of code from given source file 
		 *
		 * \param FileName Full path for processed file
		 * \param Header Header beginning code block
		 * \param End Sequence ending code block
		 * \param IncludeHeader if true, returned code will also contain header
		 * \param IncludeEnd if true, returned code will also contain ending sequence
		 */
		wxString GetCode(            
            const wxString& FileName,
            const wxString& Header,
            const wxString& End,
            bool IncludeHeader=false,
            bool IncludeEnd=false);

		/** \brief Function getting singleton object from system */
		static wxsCoder* Get() { return Singleton; }

	private:

		/** \brief Function applying hanges to currently opened editor */
		bool ApplyChanges(
            cbEditor* Editor,
            const wxString& Header,
            const wxString& End,
            wxString Code,
            bool CodeHasHeader,
            bool CodeHasEnd);
            

		/** \brief Function applying changes to file which is not open inside editor */
		bool ApplyChanges(
            const wxString& FileName,
            const wxString& Header,
            const wxString& End,
            wxString  Code,
            bool CodeHasHeader,
            bool CodeHasEnd);

        /** \brief Rebuilding code to support current editor settings */
        void RebuildCode(wxString& BaseIndentation,wxString& Code);

        /** \brief Cutting off given number of spaces at every new line */
        wxString CutSpaces(wxString Code,int Count);

		/** \brief Mutex for this object - added in case of multi-threading shedules */
		wxMutex DataMutex;
		
		/** \brief Singleton object */
		static wxsCoder* Singleton;
};

/** \page Auto-Code Code automatically generated by wxSmith
 *
 * Here's list of automatically generated code:
 *
 * \li \c //(*EventTable($CLASSNAME) - generated in class source file, contains
 *                                  enteries for event table
 * \li \c //(*Initialize($CLASSNAME) - generated in class source file, this code
 *                                  does all resource initialization (loading
 *                                  XRC, adding widgets etc.)
 * \li \c //(*Headers($CLASSNAME) - generated in class header file, this block
 *                                  contains set of #includes including required
 *                                  header files for this resource
 * \li \c //(*Identifiers($CLASSNAME) - generated in class header file, this
 *                                  code generates identifiers for window
 *                                  items (usually enum), in case of XRC
 *                                  resource (with it's own identifier
 *                                  handling system), it will be empty
 * \li \c //(*Handlers($CLASSNAME) - generated in class header. It contains
 *                                  declarations of event handler functions,
 *                                  inside this code, user may put it's own
 *                                  event handler declarations but they must
 *                                  be in form:
 *                                     void HandlerName(eventType& event).
 *                                  This block is parsed when generating list
 *                                  of event handlers which may be used with
 *                                  given event type.
 * \li \c //(*Declarations($CLASSNAME) - declarations of window items. This
 *                                  block will contain declarations of all
 *                                  window items which have "Is Member"
 *                                  property set to true.
 *
 * Blocks which will be added in future:
 *
 * \li \c //(*AppHeaders - declared in main application's source file.
 *                                 This block will contain set of #includes
 *                                 required by application.
 * \li \c //(*AppInitialize - declared in main application's source file.
 *                                 This block will automatically load resources
 *                                 and show main application's window
 */

#endif
