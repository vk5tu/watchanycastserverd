/**
 * file watchanycastdeamon.c
 *
 * @mainpage watchanycastdaemon
 */


#ifndef linux
/* Uses the Linux task accounting system. */
#error "Code specific to Linux"
#endif

#include <assert.h>
#include <netlink/netlink.h>
#include <netlink/msg.h>
#include <linux/netlink.h>
#include <linux/genetlink.h>
#include <linux/taskstats.h>
#include <stdio.h>
#include <errno.h>


/**
 * Program name and revision.
 */
static char const program_name[] = "watchanycastserverd";
static char const program_revsion[] = "$Id$";

/**
 * Command-line options.
 */
struct options_t {
#ifndef NDEBUG
    /**
     * Debugging mode. Specifically, output debug messages, output
     * messages to stderr rather than syslog, run in foreground.
     */
    int debugging;
#endif
    /**
     * List of interface names to set to down if watched server exits.
     */
    char **interface_name_list;
    /**
     * When non-NULL contains the name of a file to contain
     * the process ID of this background process. Used by
     * the init system.
     */
    char *pid_file_name;
    /**
     * List of server names to watch.
     */
    char **server_name_list;
};
/**
 * Command-line options.
 */
static struct options_t options;


/**
 * Taskstats socket additional information.
 *
 * Information about a taskstats socket that it additional to the
 * usual Netlink socket data.
 */
struct taskstats_handle_t {
    int netlink_generic_family_id;
    struct sockaddr_nl peer;
};


/**
 * Open a connection to a Netlink socket which answers the Taskstats option
 * of the Generic Netlink protocol.
 */
int taskstats_nl_connect(struct nl_handle **nl,
                         struct taskstats_handle_t *taskstats_handle) {
    struct nl_msg *msg;
    int family;
    int status;
    int length;
    struct nlmsghdr *response_message;
    int response_message_length;
    int id;
    struct nlattr *id_attribute;

    struct nlattr *attributes;
    int attributes_length;

    taskstats_handle->netlink_generic_family_id = 0;

    *nl = nl_handle_alloc();
    if (!nl) {
        perror("nl_handle_alloc()");
        return -1;
    }

    nl_disable_sequence_check(*nl);
    
    family = nl_str2nlfamily("generic");
    if (!family) {
        perror("nl_str2family(\"generic\")");
        return -1;
    }

    if (nl_connect(*nl, family)) {
        perror("nl_connect()");
        return -1;
    }

    /* Ask generic netlink for the identifier of taskstats. */
    msg = nlmsg_build_simple(GENL_ID_CTRL, NLM_F_REQUEST);

    /* Generic family header */
    struct genlmsghdr generic_header = {
        .cmd = CTRL_CMD_GETFAMILY,
        .version = 1,
    };
    nlmsg_append(msg, &generic_header, sizeof(generic_header), 1);

    /* Attribute */
    if (-1 == nla_put_string(msg,
                             CTRL_ATTR_FAMILY_NAME,
                             TASKSTATS_GENL_NAME)) {
        fprintf(stderr, "nla_put() ran out of space\n");
        return -1;
    }

    nl_send_auto_complete(*nl, nlmsg_hdr(msg));

    status = nl_send(*nl, nlmsg_hdr(msg));
    if (status < 0) {
        perror("nl_send()");
        return -1;
    }
    nlmsg_free(msg);

    response_message_length = nl_recv(*nl,
                                      &(taskstats_handle->peer),
                                      (unsigned char **)&response_message);
    if (response_message_length <= 0) {
        errno = -response_message_length;
        perror("nl_revc()");
        return -1;
    }

    id = -1;
    while (nlmsg_ok(response_message, response_message_length)) {
        id_attribute = nlmsg_find_attr(response_message,
                                       sizeof(struct genlmsghdr),
                                       CTRL_ATTR_FAMILY_ID);
        if (id_attribute) {
             taskstats_handle->netlink_generic_family_id = nla_get_u16(id_attribute);
        }
        response_message = nlmsg_next(response_message,
                                      &response_message_length);
    }

    return 0;
}
    
int taskstats_nl_read(struct nl_handle **nl,
                      struct *taskstats_handle) {

    unsigned char *msg;
    int msg_length;

    msg_length = nl_recv(*nl_handle,
                         &(taskstats_handle->peer),
                         &msg);
    if (msg_length < 0) {
        errno = -status;
        perror("nl_recv()");
        exit(1);
    }

    /* I think the message we are interested in contains this:
     *   nlmsghdr -- Netlink message header
     *   padding
     *   genlmsghdr -- generic betlink message header, with these attributes following:
     *   padding
     *     TASKSTATS_TYPE_AGGR_PID -- no payload
     *     TASKSTATS_TYPE_PID -- exiting tasks's PID
     *     TASKSTATS_TYPE_STATS -- struct taskstats for PID
     */
    while (nlmsg_ok(msg, msg_length)) {
        if (nlmsg_type == NLM_ERROR) {
            /* Set errno to nlmsgerr error number, perror(). */
            exit(1);
        }
        
        

        msg = nlmsg_next(msg, &msg_length);
    }


 
    return 0;
}


/**
 * main - entry point.
 */
int main(int argc,
         char *argv[]) {

    struct nl_handle *nl;
    struct taskstats_handle_t taskstats_handle;


    if (taskstats_nl_connect(&nl, &taskstats_handle)) {
        perror("taskstats_nl_connect()");
        exit(1);
    }


    /* Read 

    (void)nl_close(nl);
    (void)nl_handle_destroy(nl);

    return 0;
}
