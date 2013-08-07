
#pragma once

class Stream;
class NodeItem;

class Exporter
{
public:
    Exporter();

    // called by editor to begin exporting graph to stream
    // allows you to export any preamble you would like.
    virtual bool ExportToStream(Stream& stream);

    // called by editor for each node in graph. calls may be
    // nested in which case they are considered to be children.
    virtual bool ExportNodeBegin(Stream& stream, NodeItem* item);

    // called by editor for each node to close that node.
    // the next call to begin starts exporting a new node.
    virtual bool ExportNodeEnd(Stream& stream, NodeItem* item);

    // called by editor to export properties that belong to nodes.
    // if you add support for new property types, then you
    // must also add a specialization for that type here.
    template <typename T>
    bool ExportProperty(Stream& stream, T* property)
    {
        return true;
    }
};


