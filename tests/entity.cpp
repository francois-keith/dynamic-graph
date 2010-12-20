// Copyright 2010 Thomas Moulard.
//
// This file is part of dynamic-graph.
// dynamic-graph is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// dynamic-graph is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License
// along with dynamic-graph.  If not, see <http://www.gnu.org/licenses/>.

#include <sstream>
#include <dynamic-graph/entity.h>
#include <dynamic-graph/exception-factory.h>

#define BOOST_TEST_MODULE entity

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_CASE (constructor)
{
  BOOST_CHECK_EQUAL (dynamicgraph::Entity::CLASS_NAME, "Entity");

  dynamicgraph::Entity entity ("my-entity");
  BOOST_CHECK_EQUAL (entity.getName (), "my-entity");
  BOOST_CHECK_EQUAL (entity.getClassName (), dynamicgraph::Entity::CLASS_NAME);

  dynamicgraph::Entity entity2 ("");
}

BOOST_AUTO_TEST_CASE (signal)
{
  dynamicgraph::Entity entity ("");

  // Non const getter.
  try
    {
      entity.getSignal ("I do not exist");
    }
  catch (dynamicgraph::ExceptionFactory& exception)
    {
      //FIXME: getCode should be const.
      BOOST_CHECK_EQUAL (exception.getCode (),
			 dynamicgraph::ExceptionFactory::UNREFERED_SIGNAL);
    }

  // Const getter.
  try
    {
      const dynamicgraph::Entity& entityConst = entity;
      entityConst.getSignal ("I do not exist");
    }
  catch (dynamicgraph::ExceptionFactory& exception)
    {
      //FIXME: getCode should be const.
      BOOST_CHECK_EQUAL (exception.getCode (),
			 dynamicgraph::ExceptionFactory::UNREFERED_SIGNAL);
    }
}

BOOST_AUTO_TEST_CASE (displaySignalList)
{
  dynamicgraph::Entity entity ("my-entity");

  output_test_stream output;

  entity.displaySignalList(output);
  BOOST_CHECK (output.is_equal ("--- <my-entity> signal list: \n"));
}

BOOST_AUTO_TEST_CASE (display)
{
  dynamicgraph::Entity entity ("my-entity");

  output_test_stream output;

  entity.display(output);
  BOOST_CHECK (output.is_equal ("Entity: my-entity"));
}

BOOST_AUTO_TEST_CASE (getCommandList)
{
  dynamicgraph::Entity entity ("my-entity");

  //FIXME: this is wrong, another available command is help.
  BOOST_CHECK_EQUAL (entity.getCommandList (), "print\nsignals\nsignalDep");
}

BOOST_AUTO_TEST_CASE (commandLine_help)
{
  dynamicgraph::Entity entity ("my-entity");

  output_test_stream output;

  std::istringstream args;

  entity.commandLine("help", args, output);
  BOOST_CHECK
    (output.is_equal
     (
      "Entity : \n"
      "  - print\t\t\tWhat d'you think?\n"
      "  - signals\t\t\tDisplay the signals list.\n"
      "  - signalDep <signame> \tDisplay the dependency graph for signal signame.\n"
      ));
}

BOOST_AUTO_TEST_CASE (commandLine_print)
{
  dynamicgraph::Entity entity ("my-entity");

  output_test_stream output;

  std::istringstream args;

  entity.commandLine("print", args, output);
  BOOST_CHECK (output.is_equal ("Entity: my-entity\n"));
}

BOOST_AUTO_TEST_CASE (commandLine_signals)
{
  dynamicgraph::Entity entity ("my-entity");

  output_test_stream output;

  std::istringstream args;

  entity.commandLine("signals", args, output);
  BOOST_CHECK (output.is_equal ("--- <my-entity> signal list: \n"));
}

// FIXME: is it what we should expect?
BOOST_AUTO_TEST_CASE (commandLine_signalDep)
{
  dynamicgraph::Entity entity ("my-entity");

  output_test_stream output;

  std::istringstream args;

  try
    {
      entity.commandLine("signalDep", args, output);
    }
  catch (dynamicgraph::ExceptionFactory& exception)
    {
      //FIXME: getCode should be const.
      BOOST_CHECK_EQUAL (exception.getCode (),
			 dynamicgraph::ExceptionFactory::UNREFERED_SIGNAL);
    }

  BOOST_CHECK (output.is_empty ());
}

BOOST_AUTO_TEST_CASE (writeGraph)
{
  dynamicgraph::Entity entity ("my-entity");

  output_test_stream output;
  entity.writeGraph (output);

  BOOST_CHECK (output.is_equal (""));
}

BOOST_AUTO_TEST_CASE (writeCompletionList)
{
  dynamicgraph::Entity entity ("my-entity");

  output_test_stream output;
  entity.writeGraph (output);

  BOOST_CHECK (output.is_equal (""));
}

// WTF?
BOOST_AUTO_TEST_CASE (wtf)
{
  dynamicgraph::Entity entity ("my-entity");
  BOOST_CHECK_EQUAL (entity.test (),
		     static_cast<dynamicgraph::SignalBase<int>*> (0));

  entity.test2 (static_cast<dynamicgraph::SignalBase<int>*> (0));
}