void start_engine(void);
void stop_engine(void);
enum e_cmd_status run_diags(void);
int OS_Send_Msg( int, void *);
int OS_Wait_For_Msg(void *);

// Log Task ID

#define LOG_TASK 255

enum e_msg_type
{
    MT_RUN_DIAGNOSTICS,
    MT_START_ENGINE,
    MT_STOP_ENGINE,
}
  ;

enum e_cmd_status
{
    STATUS_GOOD,
    STATUS_BAD,
}
  ;

int engine_running = 0;


struct s_cmd_msg
{
  enum e_msg_type msg_type;
  int msg_len;
  char dat[100];
};

typedef struct s_cmd_msg t_cmd_msg;


struct s_log_msg
{
  enum e_cmd_status status;
  enum e_msg_type   msg_type;
  char *msg;
};

typedef struct s_log_msg t_log_msg;


void MotorControl_Task1(void)
{
    enum e_cmd_status rc;
    t_cmd_msg  command_msg;
    t_log_msg log_msg;

    while(1)
    {
        OS_Wait_For_Msg(&command_msg);
	
	    // Process the Received Message
	
  	    switch (command_msg.msg_type)
	    {
        case MT_RUN_DIAGNOSTICS:
            if (!engine_running) start_engine();
            rc = run_diags();
            engine_running = 1;
            break;
        case MT_START_ENGINE:
            if (!engine_running) start_engine();
            rc = STATUS_GOOD;
            engine_running = 1;
            break;
        case MT_STOP_ENGINE:
            if (engine_running) stop_engine();
            rc = STATUS_GOOD;
            engine_running = 0;
            break;
        default:
            rc = STATUS_BAD;
            break;
        }
    
        log_msg.status = rc;
        log_msg.msg = "Engine Control Message Received";

        OS_Send_Msg( LOG_TASK, &log_msg );
      
    }

}






enum e_cmd_status ProcessEngineMsg(t_cmd_msg *command_msg);

void MotorControl_Task2(void)
{
    enum e_cmd_status rc;
    t_cmd_msg  command_msg;
    t_log_msg log_msg;

    while(1)
    {
        OS_Wait_For_Msg(&command_msg);
	
        rc = ProcessEngineMsg(&command_msg);

        log_msg.status = rc;
        log_msg.msg = "Engine Control Message Received";

        OS_Send_Msg( LOG_TASK, &log_msg );
    }

}


enum e_cmd_status ProcessEngineMsg(t_cmd_msg *command_msg)
{
    enum e_cmd_status rc;

	switch (command_msg->msg_type)
	{
    case MT_RUN_DIAGNOSTICS:
        if (!engine_running) start_engine();
        rc = run_diags();
        engine_running = 1;
        break;

    case MT_START_ENGINE:
        if (!engine_running) start_engine();
        rc = STATUS_GOOD;
        engine_running = 1;
        break;

    case MT_STOP_ENGINE:
        if (engine_running) stop_engine();
        rc = STATUS_GOOD;
        engine_running = 0;
        break;

    default:
        rc = STATUS_BAD;
        break;
    }

    return(rc);

}
