#include  <gtk/gtk.h>

/* Rotina disparada quando o evento "fechar janela principal" ocorre */
void  on_window_closed (GtkWidget  *Widget ,  gpointer  dados) 
{ 
    gtk_main_quit  (); 
}

/* Rotina disparada quando o evento "botao contador clicado" ocorre */
void  on_botao_clicked(GtkWidget  *thisButton,  GtkWidget  *count) {
	
	static int cont = 0;
	char msg[4];
	
	cont++;
	if (cont>999) cont = 0;
	sprintf(msg, "%d", cont);
	gtk_entry_set_text(GTK_ENTRY(count), msg);
}

int  main(int argc, char *argv []) 
{ 
    GtkBuilder *builder;
	GtkWidget  *janela , *botao, *contador;

    /* Inicializar sistema GUI */ 
    gtk_init(& argc, &argv ); 
    
	builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "CountGtkXML.ui", NULL);
	
	/* Acessar o widget "Janela" a partir do Builder */ 
    janela = GTK_WIDGET(gtk_builder_get_object(builder, "gtk_janela"));
    
	/* Associar a rotina de fechar a janela ao evento "fechar a janela" */ 
    g_signal_connect(janela ,  "destroy" ,  G_CALLBACK(on_window_closed),  NULL ); 
    
	/* Acessar widget "botao" que ao ser clicado incrementa o campo do widget "contador" */ 
    botao = GTK_WIDGET(gtk_builder_get_object(builder, "gtk_botao"));		// acessa o widget "botao"
	
	/* Acessar o widget "contador" que mostra o texto da variavel que controla o contador */ 
	contador = GTK_WIDGET(gtk_builder_get_object(builder, "gtk_contador"));    // acessa o widget "contador"
		
	/* Associar a rotina de incrementar o contador e mostrar ao evento "clicar botao" */ 
	g_signal_connect(botao , "clicked" ,  G_CALLBACK(on_botao_clicked),  contador);
	 
	/* Exibir os widgets "janela" e todos os seus widgets internos  */ 
    gtk_widget_show_all(janela); 
    	
	/* Ciclo principal de eventos */ 
    gtk_main();

    return(0); 
}