/**
 * Project SearchEngine
 */

#ifndef _SEARCHENGINESERVER_H
#define _SEARCHENGINESERVER_H

class SearchEngineServer {
 public:
  void start();

  void stop();

  void onConnection();

  void onMessage();

  void onClose();

  /**
   * @param const TcpConnectionPtr&
   * @param string &msg
   */
  void doTaskThread(void const TcpConnectionPtr &, void string &msg);

 private:
  Threadpool _threadpool;
  TcpServer _tcpserver;
};

#endif  //_SEARCHENGINESERVER_H