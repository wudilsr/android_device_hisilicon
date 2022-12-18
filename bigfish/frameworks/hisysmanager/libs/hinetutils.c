#include <stdio.h>
#include <stdlib.h>
#include <utils/Log.h>
#include <netutils/ifc.h>

int enableInterface(const char *interface)
{
    return ifc_enable(interface);
}

int disableInterface(const char *interface)
{
    return ifc_disable(interface);
}

int addRoute(const char *interface, const char *dst, int prefix_length, const char *gw)
{
    return ifc_add_route(interface, dst, prefix_length, gw);
}

int setDefaultRoute(const char *interface, int gw)
{
    return ifc_set_default_route(interface, gw);
}

int removeDefaultRoute(const char *interface)
{
    return ifc_remove_default_route(interface);
}

int removeNetRoute(const char *interface)
{
    return ifc_remove_net_routes(interface);
}

int removeRoute(const char *interface, const char *dst, int prefix_length, const char *gw)
{
    return ifc_remove_route(interface, dst, prefix_length, gw);
}
