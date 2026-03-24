#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    GtkWidget *entry_user;
    GtkWidget *radio_student;
    GtkWidget *label_result;
} AppWidgets;

static void on_search_clicked(GtkButton *button, gpointer user_data) {
    (void)button;
    AppWidgets *w = (AppWidgets *)user_data;
    const char *user = gtk_entry_get_text(GTK_ENTRY(w->entry_user));

    const char *profil = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w->radio_student))
                              ? "etudiant"
                              : "enseignant";

    char cmd[512];
    snprintf(cmd, sizeof(cmd),
             "curl -s -X POST \"https://entfront.univ-lr.fr/php/wsBM.php\" -d \"uid=%s&profil=%s\"",
             user, profil);

    FILE *pipe = popen(cmd, "r");

    char response[128] = {0};
    fgets(response, sizeof(response), pipe);
    pclose(pipe);

    int count = atoi(response);
    char out[128];
    snprintf(out, sizeof(out), "Emails: %d", count);
    gtk_label_set_text(GTK_LABEL(w->label_result), out);
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "LR Email Counter");
    gtk_window_set_default_size(GTK_WINDOW(window), 360, 180);
    gtk_container_set_border_width(GTK_CONTAINER(window), 12);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *label_user = gtk_label_new("Nom:");
    GtkWidget *entry_user = gtk_entry_new();

    GtkWidget *radio_student = gtk_radio_button_new_with_label(NULL, "Etudiant");
    GtkWidget *radio_prof = gtk_radio_button_new_with_label_from_widget(
        GTK_RADIO_BUTTON(radio_student), "Prof");

    GtkWidget *button_search = gtk_button_new_with_label("Rechercher");
    GtkWidget *label_result = gtk_label_new("Emails: -");

    gtk_box_pack_start(GTK_BOX(box), label_user, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), entry_user, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), radio_student, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), radio_prof, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), button_search, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), label_result, FALSE, FALSE, 0);

    AppWidgets w = {
        .entry_user = entry_user,
        .radio_student = radio_student,
        .label_result = label_result,
    };

    g_signal_connect(button_search, "clicked", G_CALLBACK(on_search_clicked), &w);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
