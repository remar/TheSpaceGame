#include "FileDialog.h"
#include <iostream>

#ifndef _WIN32
#include <gtk/gtk.h>
#else
#include <windows.h>
#endif


std::string ChooseFile() {
#ifndef _WIN32
  
  // LINUX FILE DIALOG
  
  gtk_init_check(NULL, NULL);
  char *outPath = 0;
  GtkWidget* dialog = gtk_file_chooser_dialog_new("Open File",
						  NULL,
						  GTK_FILE_CHOOSER_ACTION_OPEN,
						  "_Cancel", GTK_RESPONSE_CANCEL,
						  "_Open", GTK_RESPONSE_ACCEPT,
						  NULL );
  if ( gtk_dialog_run( GTK_DIALOG(dialog) ) == GTK_RESPONSE_ACCEPT ) {
    char *filename;

    filename = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
	
    {
      size_t len = strlen(filename);
      outPath = new char[len+1];
      memcpy( outPath, filename, len + 1 );
      if ( !*outPath )
	{
	  g_free( filename );
	  gtk_widget_destroy(dialog);
	  return "";
	}
    }
    g_free( filename );
  }
  while (gtk_events_pending())
    gtk_main_iteration();
  gtk_widget_destroy(dialog);
  while (gtk_events_pending())
    gtk_main_iteration();

  return outPath;
#else
  OPENFILENAME ofn;
  char fileName[MAX_PATH] = "";
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = NULL;
  ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  ofn.lpstrDefExt = "";
  std::string fileNameStr;
  if ( GetOpenFileName(&ofn) )
    fileNameStr = fileName;
  return fileNameStr;
#endif
}
