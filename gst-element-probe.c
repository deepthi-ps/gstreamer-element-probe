#include <gst/gst.h>
#include <stdio.h>

GstElement* getEncoder (const char* format);
GstElement* getParser (const char* format);


int main(int argc, char **argv)
{
    gst_init (&argc, &argv);
    GstElement *h264encoder = getEncoder ("video/x-h264");
    GstElement *h264parser = getParser ("video/x-h264");
    printf ("\n Encoder Name : %s and Parser name : %s \n", gst_element_get_name (h264encoder), gst_element_get_name (h264parser));

    return 0;
}


GstElement* getEncoder (const char* format)
{
    GList *encoder_list, *encoders;
    GstCaps *caps_str;
    GstElementFactory *encoder_factory;
    GstElement *encoder = NULL;
    caps_str = gst_caps_from_string (format);

    encoder_list = gst_element_factory_list_get_elements (GST_ELEMENT_FACTORY_TYPE_ENCODER, GST_RANK_MARGINAL);
    encoders = gst_element_factory_list_filter(encoder_list, caps_str, GST_PAD_SRC, FALSE);

    if (!(g_list_length(encoders)))
    {
        gst_plugin_feature_list_free (encoder_list);
        gst_plugin_feature_list_free (encoders);
        printf("\n Couldnt find encoder \n");
        return NULL;
    }
    encoder_factory = GST_ELEMENT_FACTORY (g_list_first(encoders)->data);
    printf("\n Found encoder : %s \n", GST_ELEMENT_NAME(encoder_factory));
    if (encoder_factory != NULL)
        encoder = gst_element_factory_create (encoder_factory, NULL);

    gst_caps_unref (caps_str);
    gst_plugin_feature_list_free (encoder_list);
    gst_plugin_feature_list_free (encoders);

    return encoder;
}

GstElement* getParser (const char* format)
{
    GList *parser_list, *parsers;
    GstCaps *caps_str;
    GstElementFactory *parser_factory;
    GstElement *parser = NULL;
    caps_str = gst_caps_from_string (format);

    parser_list = gst_element_factory_list_get_elements (GST_ELEMENT_FACTORY_TYPE_PARSER, GST_RANK_MARGINAL);
    parsers = gst_element_factory_list_filter(parser_list, caps_str, GST_PAD_SINK, FALSE);

    if (!(g_list_length(parsers)))
    {
        gst_plugin_feature_list_free (parser_list);
        gst_plugin_feature_list_free (parsers);
        printf("\n Couldnt find parser \n");
        return NULL;
    }
    parser_factory = GST_ELEMENT_FACTORY (g_list_first(parsers)->data);
    printf("\n Found parser : %s \n", GST_ELEMENT_NAME(parser_factory));
    if (parser_factory != NULL)
        parser = gst_element_factory_create (parser_factory, NULL);

    gst_caps_unref (caps_str);
    gst_plugin_feature_list_free (parser_list);
    gst_plugin_feature_list_free (parsers);

    return parser;
}

