import QtQuick 2.0
import QtQuick.Controls 2.2
import QtLocation 5.3
import QtPositioning 5.0

Item
{
    Plugin
    {
        id: mapPlugin
        locales: "fr_FR"
        name: "osm" // OpenStreetMap
    }

    Map
    {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(43.95, 4.8167) // Avignon
        zoomLevel: 14
    }
}
