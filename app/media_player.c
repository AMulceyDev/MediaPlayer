#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <gtk/gtk.h>

// Media Player by Amaury Mulcey

#define MAX_IMAGES 256
#define MAX_PATH   512

typedef struct Image {
    char path[MAX_PATH];
    char name[MAX_PATH];
} Image;

typedef struct MediaPlayer {
    Image     images[MAX_IMAGES];
    int       totalImages;
    int       currentIndex;
    GtkWidget *window;
    GtkWidget *imageView;
    GtkWidget *labelCounter;
} MediaPlayer;

int isImageFile(const char *filename) {
    char *extensions[] = {".jpg", ".jpeg", ".png"};
    int nbExtensions = sizeof(extensions) / sizeof(extensions[0]);

    char *dot = strrchr(filename, '.');
    if (!dot) return 0;

    for (int i = 0; i < nbExtensions; i++) {
        if (strcmp(dot, extensions[i]) == 0) return 1;
    }
    return 0;
}

int loadImages(MediaPlayer *player, const char *dirPath) {
    DIR *dir = opendir(dirPath);
    if (!dir) return 0;

    struct dirent *entry;
    player->totalImages = 0;

    while ((entry = readdir(dir)) != NULL && player->totalImages < MAX_IMAGES) {
        if (isImageFile(entry->d_name)) {
            strncpy(player->images[player->totalImages].name, entry->d_name, MAX_PATH - 1);
            snprintf(player->images[player->totalImages].path, MAX_PATH, "%s/%s", dirPath, entry->d_name);
            player->totalImages++;
        }
    }

    closedir(dir);
    return player->totalImages;
}

void refreshImage(MediaPlayer *player) {
    if (player->totalImages == 0) return;

    GdkPixbuf *raw = gdk_pixbuf_new_from_file(player->images[player->currentIndex].path, NULL);
    if (!raw) return;

    int winW, winH;
    gtk_window_get_size(GTK_WINDOW(player->window), &winW, &winH);

    int maxW = winW;
    int maxH = winH - 60;
    int srcW = gdk_pixbuf_get_width(raw);
    int srcH = gdk_pixbuf_get_height(raw);
    double scale = (double)maxW / srcW;
    if (srcH * scale > maxH) scale = (double)maxH / srcH;

    GdkPixbuf *scaled = gdk_pixbuf_scale_simple(raw, (int)(srcW * scale), (int)(srcH * scale), GDK_INTERP_BILINEAR);
    g_object_unref(raw);

    gtk_image_set_from_pixbuf(GTK_IMAGE(player->imageView), scaled);
    g_object_unref(scaled);

    char counter[32];
    snprintf(counter, sizeof(counter), "%d / %d", player->currentIndex + 1, player->totalImages);
    gtk_label_set_text(GTK_LABEL(player->labelCounter), counter);
}

void onPrevClicked(GtkWidget *widget, gpointer data) {
    MediaPlayer *player = (MediaPlayer *)data;
    if (player->currentIndex > 0) {
        player->currentIndex--;
        refreshImage(player);
    }
}

void onNextClicked(GtkWidget *widget, gpointer data) {
    MediaPlayer *player = (MediaPlayer *)data;
    if (player->currentIndex < player->totalImages - 1) {
        player->currentIndex++;
        refreshImage(player);
    }
}

void buildUI(MediaPlayer *player) {
    player->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(player->window), "Media Player");
    gtk_window_set_default_size(GTK_WINDOW(player->window), 800, 600);
    g_signal_connect(player->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_margin_top(mainBox, 8);
    gtk_widget_set_margin_bottom(mainBox, 8);
    gtk_container_add(GTK_CONTAINER(player->window), mainBox);

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_box_pack_start(GTK_BOX(mainBox), scroll, TRUE, TRUE, 0);

    player->imageView = gtk_image_new();
    gtk_container_add(GTK_CONTAINER(scroll), player->imageView);

    GtkWidget *navBar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(navBar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(mainBox), navBar, FALSE, FALSE, 0);

    GtkWidget *btnPrev = gtk_button_new_with_label("< Prev");
    g_signal_connect(btnPrev, "clicked", G_CALLBACK(onPrevClicked), player);
    gtk_box_pack_start(GTK_BOX(navBar), btnPrev, FALSE, FALSE, 8);

    player->labelCounter = gtk_label_new("0 / 0");
    gtk_widget_set_margin_start(player->labelCounter, 16);
    gtk_widget_set_margin_end(player->labelCounter, 16);
    gtk_box_pack_start(GTK_BOX(navBar), player->labelCounter, FALSE, FALSE, 0);

    GtkWidget *btnNext = gtk_button_new_with_label("Next >");
    g_signal_connect(btnNext, "clicked", G_CALLBACK(onNextClicked), player);
    gtk_box_pack_start(GTK_BOX(navBar), btnNext, FALSE, FALSE, 8);
}

int main(int argc, char *argv[]) {
    printf("Media Player by Amaury Mulcey\nVirus by Julien Linares\n\n");
    gtk_init(&argc, &argv);

    MediaPlayer player;
    player.currentIndex = 0;

    const char *dirPath = ".";
    loadImages(&player, dirPath);

    buildUI(&player);
    gtk_widget_show_all(player.window);
    refreshImage(&player);

    gtk_main();
    return 0;
}