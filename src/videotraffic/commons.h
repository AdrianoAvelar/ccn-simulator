/*
 * File:   Commons.h
 * Author: adriano
 *
 * Created on 5 de Fevereiro de 2014, 17:19
 */

#ifndef COMMONS_H
#define COMMONS_H


#define MAX_FRAGMENTED_SIZE   1024

//It's used to know what kind of content is
//% - dummy
//# - real video file
#define DUMMY_TAG "%"
#define VIDEO_TAG "#"


struct tracerec {
    unsigned long trec_time; /* inter-packet time (usec) */
    unsigned long trec_size; /* frame size (bytes) */
    unsigned long trec_type; /* packet type */
    unsigned long trec_prio; /* packet priority */
    unsigned long trec_max; /* maximun fragmented size (bytes) */
 } ;

 typedef struct tracerec tracerec_t;

 enum kinds{
        SEND_OP = 1,
        START_DUMMY = 2,
        STOP_DUMMY =3,
        WAIT_OP = 4,
        FINISH_OP = 5,
        TIMEOUT = 6,
        STOP_SIMULATION = 7,
        EVALUATE = 8,
        EVALUATE_INCOMPLETED_FILE = 9
    };

#ifndef L
  #define L 152064 /* (352 * 288 * 1.5) */
#else
  #error "L defined elsewhere"
#endif

#ifndef MIN
  #define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
  #define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

typedef struct {
  unsigned id, size, retry, rest, segm;
  double t1, t2, j1, j2, d1, d2;
  char type, lost, signal, noise;
} dump_t;

typedef struct {
  dump_t *P, *F;
  unsigned long nP, nF;
} data_t;

typedef struct {
  unsigned long lH, lI, lP, lB, la, lA, nH, nI, nP, nB, na, nA;
} loss_t;



typedef enum mode_ {
  INVALID ,
  PACKET   = 1,
  FRAME    = 2,
  FILL     = 4,
  TRUNC    = 8,
  GEN      = 16,
  RAW      = 32,
  AUDIO    = 64,
  COMPLETE = 128,
  ASYNC    = 256
}; //MODE;


 enum packet_types {
     PT_TCP,
     PT_UDP,
     PT_CBR,
     PT_AUDIO,
     PT_VIDEO,
     PT_ACK,
     PT_START,
     PT_STOP,
     PT_PRUNE,
     PT_GRAFT,
     PT_GRAFTACK,
     PT_JOIN,
     PT_ASSERT,
     PT_MESSAGE,
     PT_RTCP,
     PT_RTP,
     PT_RTPROTO_DV,
     PT_CtrMcast_Encap,
     PT_CtrMcast_Decap,
     PT_SRM,
     /* simple signalling messages */
     PT_REQUEST,
     PT_ACCEPT,
     PT_CONFIRM,
     PT_TEARDOWN,
     PT_LIVE,    // packet from live network
     PT_REJECT,

     PT_TELNET,  // not needed: telnet use TCP
     PT_FTP,
     PT_PARETO,
     PT_EXP,
     PT_INVAL,
     PT_HTTP,

     /* new encapsulator */
     PT_ENCAPSULATED,
     PT_MFTP,

     /* CMU/Monarch's extnsions */
     PT_ARP,
     PT_MAC,
     PT_TORA,
     PT_DSR,
     PT_AODV,
     PT_IMEP,

     // RAP packets
     PT_RAP_DATA,
     PT_RAP_ACK,

     PT_TFRC,
     PT_TFRC_ACK,
     PT_PING,

     // Diffusion packets - Chalermek
     PT_DIFF,

     // LinkState routing update packets
     PT_RTPROTO_LS,

     // MPLS LDP header
     PT_LDP,

     // GAF packet
         PT_GAF,

     // ReadAudio traffic
     PT_REALAUDIO,

     // Pushback Messages
     PT_PUSHBACK,

 #ifdef HAVE_STL
     // Pragmatic General Multicast
     PT_PGM,
 #endif //STL

     PT_DUMMY,
     // insert new packet types here
     PT_NTYPE // This MUST be the LAST one

 };






#if defined(_WIN32)
  #include <winsock2.h>
  typedef unsigned __int64 u64;
  typedef SOCKET sock_t;
#elif defined(__linux__)
  typedef int sock_t;
  typedef unsigned long long u64;
#else
  #include <stdint.h>
  typedef int sock_t;
  typedef uint64_t u64;
#endif

enum prot { INV, UDP, TCP };


#endif  /* COMMONS_H */

