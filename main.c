#include <gtk/gtk.h>

struct Application_Widgets
{
	GtkWidget *window;
	GtkWidget *header_bar;
	GtkWidget *grid;

	GtkWidget *height_label;
	GtkWidget *weight_label;

	GtkWidget *height_entry;
	GtkWidget *weight_entry;

	GtkWidget *bmi_label;

	GtkWidget *button;
};

static void calculate_bmi(GtkWidget *widget, struct Application_Widgets *app_widgets)
{
	double height = strtod(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(app_widgets->height_entry))), NULL);
	double weight = strtod(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(app_widgets->weight_entry))), NULL);

	if (height != 0 && weight != 0) {
		char bmi[256];
		snprintf(bmi, 256, "%f", weight / (height * height) * 703.0);
		gtk_label_set_text(GTK_LABEL(app_widgets->bmi_label), bmi);
	} else {
		gtk_label_set_text(GTK_LABEL(app_widgets->bmi_label), "0.0");
	}
}

static void activate(GtkApplication *app, struct Application_Widgets *app_widgets)
{
	app_widgets->window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(app_widgets->window), "BMI Calculator");

	//app_widgets->header_bar = gtk_header_bar_new();

	app_widgets->grid = gtk_grid_new();

	app_widgets->height_label = gtk_label_new("Height (Inches): ");
	gtk_widget_set_margin_start(app_widgets->height_label, 10);
	gtk_widget_set_margin_end(app_widgets->height_label, 10);
	gtk_widget_set_margin_top(app_widgets->height_label, 10);
	gtk_widget_set_margin_bottom(app_widgets->height_label, 10);

	app_widgets->weight_label = gtk_label_new("Weight (Pounds): ");
	gtk_widget_set_margin_start(app_widgets->weight_label, 10);
	gtk_widget_set_margin_end(app_widgets->weight_label, 10);
	gtk_widget_set_margin_top(app_widgets->weight_label, 10);
	gtk_widget_set_margin_bottom(app_widgets->weight_label, 10);

	app_widgets->height_entry = gtk_entry_new();
	gtk_widget_set_margin_start(app_widgets->height_entry, 10);
	gtk_widget_set_margin_end(app_widgets->height_entry, 10);
	gtk_widget_set_margin_top(app_widgets->height_entry, 10);
	gtk_widget_set_margin_bottom(app_widgets->height_entry, 10);

	app_widgets->weight_entry = gtk_entry_new();
	gtk_widget_set_margin_start(app_widgets->weight_entry, 10);
	gtk_widget_set_margin_end(app_widgets->weight_entry, 10);
	gtk_widget_set_margin_top(app_widgets->weight_entry, 10);
	gtk_widget_set_margin_bottom(app_widgets->weight_entry, 10);

	app_widgets->bmi_label = gtk_label_new("0.0");
	gtk_widget_set_margin_start(app_widgets->bmi_label, 10);
	gtk_widget_set_margin_end(app_widgets->bmi_label, 10);
	gtk_widget_set_margin_top(app_widgets->bmi_label, 10);
	gtk_widget_set_margin_bottom(app_widgets->bmi_label, 10);

	app_widgets->button = gtk_button_new_with_label("Calculate");
	gtk_widget_set_margin_start(app_widgets->button, 10);
	gtk_widget_set_margin_end(app_widgets->button, 10);
	gtk_widget_set_margin_top(app_widgets->button, 10);
	gtk_widget_set_margin_bottom(app_widgets->button, 10);

	g_signal_connect(app_widgets->button, "clicked", G_CALLBACK(calculate_bmi), app_widgets);

	gtk_grid_attach(GTK_GRID(app_widgets->grid), app_widgets->height_label, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(app_widgets->grid), app_widgets->height_entry, 1, 0, 1, 1);

	gtk_grid_attach(GTK_GRID(app_widgets->grid), app_widgets->weight_label, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(app_widgets->grid), app_widgets->weight_entry, 1, 1, 1, 1);

	gtk_grid_attach(GTK_GRID(app_widgets->grid), app_widgets->bmi_label, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(app_widgets->grid), app_widgets->button, 0, 3, 1, 1);

	//gtk_window_set_child(GTK_WINDOW(app_widgets->window), app_widgets->header_bar);
	gtk_window_set_child(GTK_WINDOW(app_widgets->window), app_widgets->grid);

	gtk_window_present(GTK_WINDOW(app_widgets->window));
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	struct Application_Widgets *app_widgets;
	int status;

	app_widgets = malloc(sizeof(struct Application_Widgets));

	app = gtk_application_new("bmi.calculator", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), app_widgets);

	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	free(app_widgets);

	return status;
}