#include <BaseClasses/App.h>
#include <Scenes/DataViewer.h>


int main() {
    App app;
    app.Start();

    DataViewer* dataViewer = new DataViewer();
    dataViewer->Load();

    app.Run();
    return 0;
}
