#include <logout.h>
bool logout ( msg_ptr log, user_map_ptr smp )
{
    //Сменить статус у соответствующего User на Offline и выполнить функцию Notify_all
    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        if ( ( it->get ()->getLogin () ) == *log ) {
            it->get ()->getSock ()->close ();
            it->get ()->setStatus ( Offline );
            it->get ()->Notify_all ();
        }
    }
}